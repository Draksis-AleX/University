#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <sys/sem.h>
#include <ctype.h>

#define SHM_SIZE sizeof(long) * 3

typedef struct 
{
    char op;
    long operand;
} Op;

void P(int shm_id);
void MNG(int shm_id, int sem_read, int sem_op);
void ADD(int shm_id, int sem_read, int sem_op);
void SUB(int shm_id, int sem_read, int sem_op);
void MUL(int shm_id, int sem_read, int sem_op);

int main(int argc, char const *argv[])      //--------MAIN-------------------
{   

    int shm_id = shmget(IPC_PRIVATE, SHM_SIZE, IPC_CREAT | 0600);   // Zona di memoria condivisa
    if (shm_id == -1) {
        perror("\n\n<< Errore >> : Impossibile creare la zona di memoria condivisa.\n\n");
        exit(1);
    }

    int sem_read = semget(IPC_PRIVATE, 1, IPC_CREAT | 0600);    // Semaforo per la lettura del file
    if (sem_read == -1)
    {
        perror("\n\n<< Errore >> : Imposibile creare semaforo sem_read.\n\n");
        exit(1);
    }

    if (semctl(sem_read, 0, SETVAL, 0) == -1) {
        perror("\n\n<< Errore >> : Impossibile settare a 0 sem_read.");
        exit(1);
    }

    int sem_op = semget(IPC_PRIVATE, 3, IPC_CREAT | 0600);    // Semaforo per le operazioni
    if (sem_op == -1)
    {
        perror("\n\n<< Errore >> : Imposibile creare semaforo sem_op.\n\n");
        exit(1);
    }

    for (int i = 0; i < 3; i++)
    {
        if (semctl(sem_op, i, SETVAL, 0) == -1) {
            perror("\n\n<< Errore >> : Impossibile settare a 0 sem_op.");
            exit(1);
        }
    }
    

    //------------------------------------------------------------------------------------------
    
    int pid = fork();
    if (pid != -1 && pid == 0) {    // Figlio MNG
        MNG(shm_id, sem_read, sem_op);
        exit(0);
    }
    else if (pid == -1) perror("\n\n<< Errore >> : Impossibile Creare figlio MNG.\n\n");

    int pid_add = fork();
    if (pid_add != -1 && pid_add == 0) {    // Figlio ADD
        ADD(shm_id, sem_read, sem_op);
        exit(0);
    }
    else if (pid == -1) perror("\n\n<< Errore >> : Impossibile Creare figlio ADD.\n\n");

    int pid_sub = fork();
    if (pid_sub != -1 && pid_sub == 0) {    // Figlio SUB
        SUB(shm_id, sem_read, sem_op);
        exit(0);
    }
    else if (pid == -1) perror("\n\n<< Errore >> : Impossibile Creare figlio SUB.\n\n");

    int pid_mul = fork();
    if (pid_mul != -1 && pid_mul == 0) {    // Figlio MUL
        MUL(shm_id, sem_read, sem_op);
        exit(0);
    }
    else if (pid == -1) perror("\n\n<< Errore >> : Impossibile Creare figlio MUL.\n\n");
    

    //------------------------------------------------------------------------------------------

    
    for (int i = 0; i < 4; i++)
    {
        wait(NULL);
    }
    
    
    
    if (shmctl(shm_id, IPC_RMID, NULL) == -1) perror("\n\n<< Errore >> : Impossibile distruggere zona di memoria condivisa.\n\n");
    if (semctl(sem_read, 1, IPC_RMID) == -1) perror("\n\n<< Errore >> : Impossibile eliminare sem_read.\n\n");
    if (semctl(sem_op, 3, IPC_RMID) == -1) perror("\n\n<< Errore >> : Impossibile eliminare sem_op.\n\n");

    return 0;
}



void MNG(int shm_id, int sem_read, int sem_op){     //------------ Figlio che gestisce i calcoli ------------------

    struct sembuf WAIT[1] = { { 0, -1, 0 } };
    struct sembuf SIGNAL[1] = { { 0, +1, 0 } };

    long *shared_space;

    if ((shared_space = (long *) shmat(shm_id, NULL, 0)) == (long *) -1) {
        perror ("\n\n<< Errore >> : Impossibile associare memoria condivisa a MNG.\n\n");
        exit(1);
    }

    FILE *file = fopen("List-1.txt", "r");
    if (file == NULL) perror("\n\n<< Errore >> : Impossibile aprire il file.\n\n");
    Op op_buff;
    op_buff.op = ' ';
    op_buff.operand = 0;
    char line[1000];

    shared_space[0] = 0;

    while (fgets(line, sizeof(line), file))
    {

        sscanf(line, "%c%ld", &op_buff.op, &op_buff.operand);

        //-------------------------------------------------------------

        printf("\nMNG - [ Risultato intermedio : %ld ] [ Letto : %c %ld ]\n", shared_space[0], op_buff.op, op_buff.operand);

        shared_space[1] = op_buff.operand;

        //-----------------------------------------------------------

        switch (op_buff.op)
        {
        case '+':
        
            SIGNAL[0].sem_num = 0;
            semop(sem_op, SIGNAL, 1);   // Sveglio figlio ADD

            break;

        case '-':

            SIGNAL[0].sem_num = 1;
            semop(sem_op, SIGNAL, 1);   // Sveglio figlio SUB

            break;

        case '*':

            SIGNAL[0].sem_num = 2;
            semop(sem_op, SIGNAL, 1);   // Sveglio figlio MUL

            break;
        
        default:
            printf("\n\n<< Errore >> : Operazione da eseguire non riconosciuta.\n\n");
            break;
        }

        semop(sem_read, WAIT, 1);
    }
    
    for (int i = 0; i < 3; i++)
    {
        SIGNAL[0].sem_num = i;
        semop(sem_op, SIGNAL, 1);
    }
    
    printf("\x1b[34m\n\nMNG - \t\t[ Risultato finale : %ld ]\x1b[0m\n\n", shared_space[0]);

    shared_space[2] = -1;
    fclose(file);
    shmdt(shared_space);
}

void ADD(int shm_id, int sem_read, int sem_op){      //----------- Figlio addizione --------------

    struct sembuf WAIT[1] = { { 0, -1, 0 } };
    struct sembuf SIGNAL[1] = { { 0, +1, 0 } };
    long *shared_space;
    if ((shared_space = shmat(shm_id, NULL, 0)) == (long *) -1) {
        perror("\n\n<< Errore >> : Impossibile associare zona di memoria condivisa a ADD.\n\n");
    }

    while (1)
    {
        semop(sem_op, WAIT, 1);
        if(shared_space[2] == -1) break;

        long ris = shared_space[0] + shared_space[1];
        printf("\n\x1b[31mADD - %ld + %ld = %ld\x1b[0m\n", shared_space[0], shared_space[1], ris);
        shared_space[0] = ris;

        semop(sem_read, SIGNAL, 1);
    }

    shmdt(shared_space);
}

void SUB(int shm_id, int sem_read, int sem_op){      //----------- Figlio sottrazione --------------

    struct sembuf WAIT[1] = { { 1, -1, 0 } };
    struct sembuf SIGNAL[1] = { { 0, +1, 0 } };
    long *shared_space;
    if ((shared_space = shmat(shm_id, NULL, 0)) == (long *) -1) {
        perror("\n\n<< Errore >> : Impossibile associare zona di memoria condivisa a ADD.\n\n");
    }

    while (1)
    {
        semop(sem_op, WAIT, 1);
        if(shared_space[2] == -1) break;

        long ris = shared_space[0] - shared_space[1];
        printf("\n\x1b[31mSUB - %ld - %ld = %ld\x1b[0m\n", shared_space[0], shared_space[1], ris);
        shared_space[0] = ris;

        semop(sem_read, SIGNAL, 1);
    }

    shmdt(shared_space);
}

void MUL(int shm_id, int sem_read, int sem_op){      //----------- Figlio moltiplicazione --------------

    struct sembuf WAIT[1] = { { 2, -1, 0 } };
    struct sembuf SIGNAL[1] = { { 0, +1, 0 } };
    long *shared_space;
    if ((shared_space = shmat(shm_id, NULL, 0)) == (long *) -1) {
        perror("\n\n<< Errore >> : Impossibile associare zona di memoria condivisa a ADD.\n\n");
    }

    while (1)
    {
        semop(sem_op, WAIT, 1);
        if(shared_space[2] == -1) break;

        long ris = shared_space[0] * shared_space[1];
        printf("\n\x1b[31mMUL - %ld * %ld = %ld\x1b[0m\n", shared_space[0], shared_space[1], ris);
        shared_space[0] = ris;

        semop(sem_read, SIGNAL, 1);
    }
    shmdt(shared_space);
}

