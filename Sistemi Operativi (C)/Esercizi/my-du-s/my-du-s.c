#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <dirent.h>

#define MAX_PATH_LEN 1000
#define DIM_MSG 1024

typedef struct{
    char scanner_path[MAX_PATH_LEN];
    char file_path[MAX_PATH_LEN];
    int end;
}shm_msg;

typedef struct{
    char scanner_path[MAX_PATH_LEN];
    long size;
    int end;
}mq_msg;

typedef struct {
    long	mtype;
    char    eof;
    char	mtext[DIM_MSG];
} msg;

int WAIT(int sem_des, int num_semaforo){
    struct sembuf operazioni[1] = {{num_semaforo,-1,0}};
    return semop(sem_des, operazioni, 1);
};

int SIGNAL(int sem_des, int num_semaforo){
    struct sembuf operazioni[1] = {{num_semaforo,+1,0}};
    return semop(sem_des, operazioni, 1);
};

void error(char* msg){
    perror(msg);
    exit(1);
};

void printdir(const char *dir, const char *o_path, int sem_1, int sem_2, shm_msg* shm_mem) {
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;

    if ((dp = opendir(dir)) == NULL) error("\n\n<< Errore >> : Impossibile aprire directory.\n\n");

    if (chdir(dir) == -1) error("\n\n<< Errore >> : Impossibile cambiare directoy corrente.\n\n");

    while ((entry = readdir(dp)) != NULL) {

        lstat(entry->d_name, &statbuf);
        char current_dir[MAX_PATH_LEN];
        getcwd(current_dir, MAX_PATH_LEN);
        strcat(current_dir,"/");
        char file_path[MAX_PATH_LEN]; 
        strcpy(file_path, strcat(current_dir, entry->d_name));

        if (S_ISDIR(statbuf.st_mode)) {        

            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0 || strcmp(entry->d_name, ".DS_Store") == 0)
                continue;
      
            printdir(entry->d_name, o_path, sem_1, sem_2, shm_mem);

        } else {                            // e' un file

            printf("\n[[Scanner]] : Aspetto signal su sem1\n");
            WAIT(sem_1, 0);

            printf("\n[[Scanner]] : Invio nome file a stater.\n");
            
            strcpy(shm_mem->scanner_path, o_path);
            strcpy(shm_mem->file_path, file_path);
            shm_mem->end = 0;

            SIGNAL(sem_2, 0);

        }
    }
    chdir("..");
    
    closedir(dp);
}

//-------------------------------  S C A N N E R  ----------------------------------------------

void scanner(int shm_id, char* path, int sem_1, int sem_2){

    printf("\n[[SCANNER \"%s\" ]] : Sono stato creato.\n", path);

    shm_msg* shm_mem;
    if((shm_mem = (shm_msg*) shmat(shm_id, NULL, 0)) == (shm_msg*) -1) 
        error("\n\n[[SCANNER]] : << Errore >> : Impossibile associare zona di memoria condivisa.\n\n");

    //Scannerizzo il mio path

    printdir(path, path, sem_1, sem_2, shm_mem);

    WAIT(sem_1, 0);

    printf("\n[[Scanner]] : Invio messaggio finale a stater.\n");
            
    strcpy(shm_mem->scanner_path, path);
    strcpy(shm_mem->file_path, "nd");
    shm_mem->end = 1;

    SIGNAL(sem_2, 0);

    printf("\n[[SCANNER]] : Sono morto.\n");
    shmdt(shm_mem);
    exit(0);
}

//----------------------------------------------------------------------------------------------


//--------------------------------  S T A T E R  -----------------------------------------------

void stater(int shm_id, int msg_id, int sem_1, int sem_2, int n_paths){

    printf("\n[[STATER]] : Sono stato creato.\n");

    shm_msg* shm_mem;
    if((shm_mem = (shm_msg*) shmat(shm_id, NULL, 0)) == (shm_msg*) -1) 
        error("\n\n[[STATER]] : << Errore >> : Impossibile associare zona di memoria condivisa.\n\n");
    
    SIGNAL(sem_1, 0);
    
    struct stat statbuf;
    int ended_scanners = 0;

    while (1)
    {
        printf("\n[[STATER]] : Aspetto su sem2.\n\n");
        WAIT(sem_2, 0);
        printf("\n[[STATER]] : Eseguo.\n\n");

        //printf("\n\n[[STATER]] : File_name = %s\n\n", strcat(strcat(shm_mem->scanner_path, "/"),shm_mem->file_name));

        if(shm_mem->end == 0){
            if(lstat(shm_mem->file_path, &statbuf) == -1) error("\n\n<< Errore >> : Impossibile ottenere stats del file.\n\n");
            printf("\n[[STATER]] : File Path = \"%s\"\n", shm_mem->file_path);
            printf("\n[[STATER]] : Dimensione file: %lld\n", statbuf.st_blocks * 512);

            mq_msg msg;
            strcpy(msg.scanner_path, shm_mem->scanner_path);
            msg.size = statbuf.st_blocks * 512;
            msg.end = 0;

            printf("\n[[STATER]] : Invio messaggio al padre.\n");
            if(msgsnd(msg_id, &msg, sizeof(mq_msg) - sizeof(long), 0) < 0)
                error("\n\n<< Errore >> : Impossibile inviare messaggio sulla coda di messaggi.\n\n");
            SIGNAL(sem_1, 0);
        }
        else{
            printf("\n[[STATER]] : Scanner \"%s\" ha finito.\n", shm_mem->scanner_path);
            ended_scanners++;
            if(ended_scanners == n_paths){
                mq_msg msg;
                strcpy(msg.scanner_path, shm_mem->scanner_path);
                msg.size = 0;
                msg.end = 1;

                printf("\n[[STATER]] : Invio messaggio finale al padre.\n");
                if(msgsnd(msg_id, &msg, sizeof(mq_msg) - sizeof(long), 0) < 0)
                    error("\n\n<< Errore >> : Impossibile inviare messaggio sulla coda di messaggi.\n\n");
                SIGNAL(sem_1, 0);
                break;
            }
            else SIGNAL(sem_1, 0);
        }
    }
    
    printf("\n[[STATER]] : Sono morto.\n");
    shmdt(shm_mem);
    exit(0);
}

//----------------------------------------------------------------------------------------------


//---------------------------------  P A D R E  ------------------------------------------------

void padre(int msg_id, int n_paths, char* paths[]){

    printf("\n[[PADRE]] : Figli creati.\n");

    mq_msg msg;
    long sizes[n_paths];
    for (int i = 0; i < n_paths; i++)
    {
        sizes[i] = 0;
    }
    

    while (1)
    {
        if(msgrcv(msg_id, &msg, sizeof(mq_msg) - sizeof(long), 0, 0) < 0)
            error("\n\n<< Errore >> : Impossibile ricevere sulla coda di messaggi.\n\n");
        printf("\n[[PADRE]] : Ho ricevuto un messaggio:\n\tscannerpath: %s\n\tsize: %ld\n\tend: %d\n", msg.scanner_path, msg.size, msg.end);
        if(msg.end == 0){
            int index = -1;
            for (int i = 0; i < n_paths; i++)
            {
                if(strcmp(paths[i], msg.scanner_path) == 0){
                    index = i;
                    break;
                }
            }
            sizes[index] += msg.size;
        }
        else{
            break;
        }
    }
    
    printf("\n[[PADRE]] : Ho finito.\n");

    printf("\n\n\n << Statistiche finali >> \n");
    for (int i = 0; i < n_paths; i++)
    {
        printf("\n[ %s ] : %ld;\n", paths[i], sizes[i]);
    }
    
}

//----------------------------------------------------------------------------------------------

//----------------------------------  M A I N  -------------------------------------------------

int main(int argc, char *argv[])
{
    /*if(argc < 2) error("\n\n<< Errore >> : Numero di parametri insufficienti.\n\n");
    int n_paths = argc - 1;
    char* paths[n_paths];

    for (int i = 0; i < n_paths; i++)
    {
        paths[i] = argv[i+1];
    }*/

    int n_paths = 2;
    char* paths[n_paths];

    paths[0] = "/Users/draksis/Documents/Cazzatine";
    paths[1] = "/Users/draksis/Documents/Zoom";
    

    //---------------------  CREAZIONE IPC  -----------------------------

    int shm_id = shmget(IPC_PRIVATE, MAX_PATH_LEN, IPC_CREAT | 0600);
    if(shm_id == -1) error("\n\n<< Errore >> : Impossibile creare zona di memoria condivisa.\n\n");

    int msg_id = msgget(IPC_PRIVATE, IPC_CREAT | IPC_EXCL | 0660);
    if(msg_id == -1) error("\n\n<< Errore >> : Impossibile creare coda di messaggi.\n\n");

    int sem_1 = semget(IPC_PRIVATE, 1, IPC_CREAT | 0600);
    if(sem_1 == -1) error("\n\n<< Errore >> : Impossibile creare sem 1.\n\n");

    int sem_2 = semget(IPC_PRIVATE, 1, IPC_CREAT | 0600);
    if(sem_2 == -1) error("\n\n<< Errore >> : Impossibile creare sem 2.\n\n");

    if(semctl(sem_1, 0, SETVAL, 0) == -1) error("\n\n<< Errore >> : Impossibile settare sem 1 a 1.\n\n");

    if(semctl(sem_2, 0, SETVAL, 0) == -1) error("\n\n<< Errore >> : Impossibile settare sem 2 a 0.\n\n");

    //-------------------------------------------------------------------

    //--------------------  CREAZIONE FIGLI  ----------------------------

    int pid_stater = fork();
    if(pid_stater == 0){
        stater(shm_id, msg_id, sem_1, sem_2, n_paths);
    }

    for (int i = 0; i < n_paths; i++)
    {
        int pid_scanner = fork();
        if(pid_scanner == 0){
            scanner(shm_id, paths[i], sem_1, sem_2);
        }
    }

    padre(msg_id, n_paths, paths);

    for (int i = 0; i < n_paths + 1; i++)
    {
        if(wait(NULL) == -1) error("\n\n<< Errore >> : Impossibile aspettare figli.\n\n");
    }

    //-------------------------------------------------------------------

    //----------------------  CHIUSURA IPC  -----------------------------

    if(shmctl(shm_id, IPC_RMID, NULL) == -1) error("\n\n<< Errore >> : Impossibile rimuovere zona di memoria condivisa.\n\n");
    if(msgctl(msg_id, IPC_RMID, NULL) == -1) error("\n\n<< Errore >> :  Impossibile rimuovere coda di messaggi.\n\n");
    if(semctl(sem_1, 0, IPC_RMID, NULL) == -1) error("\n\n<< Errore >> :  Impossibile rimuovere sem 1.\n\n");
    if(semctl(sem_2, 0, IPC_RMID, NULL) == -1) error("\n\n<< Errore >> :  Impossibile rimuovere sem 2.\n\n");

    //-------------------------------------------------------------------

    return 0;
}

//----------------------------------------------------------------------------------------------
