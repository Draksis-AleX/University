
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

#define LINESIZE 2048

typedef struct{
    int word_check;
    char line[LINESIZE];
}shared_memory;

void error(char* msg){
    perror(msg);
    exit(1);
};

void printline(char* line){
    int i = 0;
    while(line[i] != '\0'){
        printf("%c", line[i]);
        i++;
    }
    printf("\n\n");
};

int WAIT(int sem_des, int num_semaforo){
    struct sembuf operazioni[1] = {{num_semaforo,-1,0}};
    return semop(sem_des, operazioni, 1);
};

int SIGNAL(int sem_des, int num_semaforo){
    struct sembuf operazioni[1] = {{num_semaforo,+1,0}};
    return semop(sem_des, operazioni, 1);
};

//-----------------------------  CORPO R  -----------------------------------------------

void R(int shm_id, int* pipe_id, char* file_name, int n_words, int sem_r, int sem_w){

    printf("\nSono R, sono stato creato!\n");
    shared_memory* shared_space;
    if ((shared_space = (shared_memory *)shmat(shm_id, NULL, 0)) == (shared_memory *)-1)
        error("\n\n << Errore >> : Impossibile associare zona di memoria condivisa.\n\n");
        

    FILE* text_file = fopen(file_name, "r");

    char line[LINESIZE];
    while (fgets(line, LINESIZE, text_file))
    {
        
        shared_space->word_check = 0;
        printf("\nwordcheck = 0\n");

        int i = 0;
        /*while (line[i] != '\0')
        {
            shared_space->line[i] = line[i];
            i++;
        }*/

        strncpy(shared_space->line, line, LINESIZE);

        //printf("\nRiga scritta nella zona di memoria.\n");

        for (int i = 0; i < n_words;i++)
        {
            if(SIGNAL(sem_w, i) == -1) error("\n\n<< Errore >> : Impossibile eseguire signal su sem_w.\n\n");
        }

        //printf("\nProcessi W svegliati.\n");
        
        for (int i = 0; i < n_words; i++)
        {
            if(WAIT(sem_r, i) == -1) error("\n\n<< Errore >> : Impossibile eseguire wait su sem_r.\n\n");
        }

        if(shared_space->word_check == n_words){
            //printf("\n\nLa seguente riga contiene tutte le parole:\n %s\n\n", line);
            if(write(pipe_id[1], line, sizeof(line) + 1) == -1)
                error("\n\n<< Errore >> : Impossibile scrivere sulla pipe.\n\n");
        }
    }

    shared_space->word_check = -1;
    
    for (int i = 0; i < n_words;i++)
    {
        if(SIGNAL(sem_w, i) == -1) error("\n\n<< Errore >> : Impossibile eseguire signal su sem_w.\n\n");
    }

    strcpy(line, "<<exit>>");

    write(pipe_id[1], line, sizeof(line));

    shmdt(shared_space);

    exit(0);
};

//---------------------------------------------------------------------------------------

//-----------------------------  CORPO O  -----------------------------------------------

void O(int* pipe_id){

    printf("\nSono O, sono stato creato!\n");

    char line[LINESIZE + 1];

    while (1)
    {
        read(pipe_id[0], line, LINESIZE + 1);
        if(strcmp(line,"<<exit>>") == 0) break;
        printf("\n\nO :: La seguente linea è presente:\n\n%s\n\n", line);
    }
    
    exit(0);
};

//---------------------------------------------------------------------------------------

//-----------------------------  CORPO W  -----------------------------------------------

void W(int shm_id, const char* word, int sem_r, int sem_w, int number){

    printf("\nSono W%d, sono stato creato!\n", number);

    shared_memory* shared_space;
    if ((shared_space = (shared_memory *)shmat(shm_id, NULL, 0)) == (shared_memory *)-1)
        error("\n\n << Errore >> : Impossibile associare zona di memoria condivisa.\n\n");

    while (1)
    {
        printf("\nW%d: Aspetto sem_w[%d]...\n", number, number);

        if(WAIT(sem_w, number) == -1) error("\n\n<< Errore >> : Impossibile eseguire wait su sem_w.\n\n");

        if(shared_space->word_check == -1) break;

        if (strcasestr(shared_space->line, word) != NULL){
            //printf("\n\x1b[31mNella riga:\x1b[0m\n%s\n\x1b[31mho trovato %s\n\n\x1b[0m", shared_space->line, word);
            shared_space->word_check++;
        }
        
        printf("\nControllo presenza parola \"%s\"...\n", word);

        if(SIGNAL(sem_r, number) == -1) error("\n\n<< Errore >> : Impossibile eseguire signal su sem_r.\n\n");
    }
    
    shmdt(shared_space);
    exit(0);
};

//---------------------------------------------------------------------------------------

//-----------------------------  M A I N  -----------------------------------------------

int main(int argc, char *argv[])
{   

    if(argc < 3) error("\n\n<< Errore >> : Numero di parametri non valido\n.");

    char* file_name = argv[1];
    const char* words[argc - 2];
    for (int i = 0; i < argc; i++)
    {
        words[i] = argv[i+2];
    }
    
    int n_words = argc - 2;

    //----------------------------- CREAZIONE IPC ------------------------------
    
    int shm_id;
    if((shm_id = shmget(IPC_PRIVATE, (n_words * sizeof(int)) + LINESIZE, IPC_CREAT | 0600)) == -1)
        error("\n\n<< Errore >> : Impossibile creare la zona di memoria condivisa.\n\n");
    
    int pipe_id[2];
    if(pipe(pipe_id) == -1) error("\n\n<< Errore >> : Impossibile creare la pipe.\n\n");

    int sem_r;
    if((sem_r = semget(IPC_PRIVATE, n_words, IPC_CREAT | 0600)) == -1)
        error("\n\n<< Errore >> : Impossibile creare sem_r.\n\n");

    for (int i = 0; i < n_words; i++)
    {
        if(semctl(sem_r, i, SETVAL, 0) == -1)
            error("<< Errore >> : Impossibile settare sem_r a 0.\n\n");
    } 
    
    int sem_w;
    if((sem_w = semget(IPC_PRIVATE, n_words, IPC_CREAT | 0600)) == -1)
        error("\n\n<< Errore >> : Impossibile creare sem_o.\n\n");

    for (int i = 0; i < n_words; i++)
    {
        if(semctl(sem_w, i, SETVAL, 0) == -1)
            error("<< Errore >> : Impossibile settare sem_w a 0.\n\n");
    }

    //---------------------------------------------------------------------------

    //----------------------------- CREAZIONE FIGLI -----------------------------

    int pid_r = fork();
    if(pid_r == 0){
        R(shm_id, pipe_id, file_name, n_words, sem_r, sem_w);
    }

    int pid_o = fork();
    if(pid_o == 0){
        O(pipe_id);
    }

    for (int i = 0; i < n_words; i++)
    {
        int pid_w = fork();
        if(pid_w == 0){
            W(shm_id, words[i], sem_r, sem_w, i);
        }
    }

    for (int i = 0; i < n_words + 2; i++){
        if(wait(NULL) == -1) error("\n\n<< Errore >> : Impossibile aspettare figli.\n\n");
    }

    //---------------------------------------------------------------------------

    //----------------------------- CHIUSURA IPC --------------------------------

    if(shmctl(shm_id, IPC_RMID, NULL) == -1) 
        error("\n\n<< Errore >> : Impossibile distruggere zona di memoria condivisa.\n\n");

    //---------------------------------------------------------------------------

    return 0;
}
