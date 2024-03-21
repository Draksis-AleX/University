#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LEN 1024

typedef struct {
    int id;
    char line[MAX_LINE_LEN];
} shm_msg;

typedef struct {
    long type;
    int id;
    int occurrencies[26];
} queue_msg;

void error(char* msg){
    printf("\n\n\x1b[31m<< Errore >>\n\t");
    perror(msg);
    printf("\x1b[0m\n\n");
    exit(1);
}

void WAIT(int sem){
    struct sembuf op[1] = {{0,-1,0}};
    if(semop(sem, op, 1) == -1) error("Impossibile eseguire wait.\n");
}

void SIGNAL(int sem){
    struct sembuf op[1] = {{0,+1,0}};
    if(semop(sem, op, 1) == -1) error("Impossibile eseguire wait.\n");
}

//-----------------------------  COUNTER  --------------------------------------

void counter(int n_files, int shm_id, int sem_r, int sem_w, int msg_id){
    printf("\x1b[32m[C] : Sono stato creato.\x1b[0m\n");

    shm_msg* shm = (shm_msg*) shmat(shm_id, NULL, 0);
    if(shm == (shm_msg*) -1) error("Impossibile associare zona di memoria condivisa.\n");
    int died_readers = 0;

    SIGNAL(sem_w);

    queue_msg msg;
    msg.type = 1;
    for(int i = 0; i < 26; i++) msg.occurrencies[i] = 0; 

    while(1){       
        WAIT(sem_r);

        if(shm->id == -1){
            died_readers++;
            if(died_readers >= n_files) break;
            else {
                SIGNAL(sem_w);
                continue;
            }
        }
        //printf("\x1b[32m[C] : Linea ricevuta da reader %d:\n.\x1b[0m\n", shm->id);

        msg.id = shm->id;

        for(int i = 0; i < 26; i++){
            
            int occurrencies = 0;

            for(int j = 0; j < strlen(shm->line); j++){
                shm->line[j] = toupper(shm->line[j]);
                if(shm->line[j] == i+65) occurrencies++;
            }
                
            msg.occurrencies[i] = occurrencies;

        }

        if(msgsnd(msg_id, &msg, sizeof(queue_msg) - sizeof(long), 0) == -1) error("Impossibile inviare messaggio sulla coda.\n");

        SIGNAL(sem_w);
    }

    //printf("\x1b[32m[C] : Mando messaggio finale al father %d:\n%s.\x1b[0m\n", shm->id, shm->line);
    msg.id = -1;
    if(msgsnd(msg_id, &msg, sizeof(queue_msg) - sizeof(long), 0) < 0) error("Impossibile inviare messaggio sulla coda.\n");   
    //printf("\x1b[32m[C] : Messaggio mandato al father %d:\n%s.\x1b[0m\n", shm->id, shm->line);


    shmdt(shm);
    exit(0);
}

//-----------------------------------------------------------------------------

//-----------------------------  READER  --------------------------------------

void reader(int id, char* filename, int shm_id, int sem_r, int sem_w){
    printf("\x1b[33m[R %d] : Sono stato creato.\x1b[0m\n", id);
    printf("\x1b[33m[R %d] : My file = \"%s\".\x1b[0m\n", id, filename);

    shm_msg* shm = (shm_msg*) shmat(shm_id, NULL, 0);
    if(shm == (shm_msg*) -1) error("Impossibile associare zona di memoria condivisa.\n");

    FILE* file = fopen(filename, "r");

    char line[MAX_LINE_LEN];
    while(fgets(line, MAX_LINE_LEN, file)){
        //printf("\x1b[33m[R %d] : %s\x1b[0m\n", id, line);

        WAIT(sem_w);

        shm->id = id;
        strcpy(shm->line, line);

        SIGNAL(sem_r);

    }

    WAIT(sem_w);

    shm->id = -1;
    strcpy(shm->line, "--end--");

    SIGNAL(sem_r);

    //printf("\x1b[33m[R %d] : Finito.\x1b[0m\n", id);

    shmdt(shm);
    fclose(file);
    exit(0);
}

//-----------------------------------------------------------------------------

void father(const int n_files, int msg_id){
    printf("[P] : Sono stato creato.\x1b[0m\n");

    queue_msg msg;

    int tot_occurrencies[n_files][26];

    for(int i = 0; i < n_files; i++){
        for(int j = 0; j < 26; j++){
            tot_occurrencies[i][j] = 0;
        }
    }

    while(1){

        if(msgrcv(msg_id, &msg, sizeof(queue_msg) - sizeof(long), 0, 0) < 0) error("Impossibile ricevere messaggio dalla coda.\n");
        //printf("[P] : Ricevuto messaggio da counter: Reader %d\n", msg.id);
        if(msg.id == -1) break;

        for(int i = 0; i < 26; i++){
            tot_occurrencies[msg.id][i] += msg.occurrencies[i];
        }

    }

    printf("[P] : FINAL STATS\n\n");

    for(int i = 0; i < n_files; i++){
        printf("\nOccorrenze delle lettere nel file %d:\n\n", i);
        for(int j = 0; j < 26; j++){
            printf("%c : %d\n", j+65, tot_occurrencies[i][j]);
        }
    }

    exit(0);
}

//-----------------------------------------------------------------------------

int main(int argc, const char* argv[]){

    char* files[3];
    files[0] = "hammer-to-fall.txt";
    files[1] = "bocca-di-rosa.txt";
    files[2] = "imagine.txt";

    const int n_files = 3;

    //----------------  DICHIARAZIONE IPC  ----------------

    int shm_id = shmget(IPC_PRIVATE, sizeof(shm_msg), IPC_CREAT | 0600);
    if(shm_id == -1) error("Impossibile creare zona di memoria condivisa.\n");

    int msg_id = msgget(IPC_PRIVATE, IPC_CREAT | IPC_EXCL | 0660);
    if(msg_id == -1) error("Impossibile creare coda di messaggi.\n");

    int sem_r = semget(IPC_PRIVATE, 1, IPC_CREAT | 0660);
    if(sem_r == -1) error("Impossibile creare sem_r.\n");
    if(semctl(sem_r, 0, SETVAL, 0) == -1) error("Impossibile settare sem_r a 0.\n");

    int sem_w = semget(IPC_PRIVATE, 1, IPC_CREAT | 0660);
    if(sem_w == -1) error("Impossibile creare sem_w.\n");
    if(semctl(sem_w, 0, SETVAL, 0) == -1) error("Impossibile settare sem_w a 0.\n");

    //-----------------------------------------------------

    //--------------  CREAZIONE FIGLI  --------------------

    for(int i = 0; i < n_files; i++){
        int pid = fork();
        if(pid == 0) reader(i, files[i], shm_id, sem_r, sem_w);
    }

    int pid_c = fork();
    if(pid_c == 0) counter(n_files, shm_id, sem_r, sem_w, msg_id);

    father(n_files, msg_id);

    for(int i = 0; i < n_files + 1; i++){
        wait(NULL);
    }

    //-----------------------------------------------------

    //------------  DISTRUZIONE IPC  ----------------------

    if(shmctl(shm_id, IPC_RMID, NULL) < 0) error("Impossibile distruggere zona di memoria condivisa.\n");
    if(msgctl(msg_id, IPC_RMID, NULL) < 0) error("Impossibile distruggere coda di messaggi.\n");
    if(semctl(sem_r, 0, IPC_RMID, NULL) < 0) error("Impossibile distruggere sem_r");
    if(semctl(sem_w, 0, IPC_RMID, NULL) < 0) error("Impossibile distruggere sem_w");

    return 0;
}