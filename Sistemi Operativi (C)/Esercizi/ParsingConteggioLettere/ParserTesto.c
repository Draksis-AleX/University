
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

typedef struct {
    long mtype;
    int charNum;
    int occurrencies;
} LineStat;


// -------------------------- P -------------------------------------------------

void P(int shm_id, int sem, int sem2) {

    struct sembuf SIGNAL[1] = { { 0, +1, 0 } };
    struct sembuf WAIT[1] = { { 0, -1, 0 } };

    int *shared_space;

    if ((shared_space = (int *)shmat(shm_id, NULL, 0)) == (int *)-1) {
        perror("shmat");
        exit(1);
    }

    FILE *file = fopen("text.txt", "r");
    if (file == NULL) perror("\n\n<< Errore >> : Impossibile aprire il file.\n\n");
    char line[1000];

    while (fgets(line, sizeof(line), file))
    {   

        printf("\nNew Line\n");

        int i = 0, j = 0;
            
        shared_space[0] = strlen(line);

        while (line[j] != '\0'){
            shared_space[++i] = line[j];
            j++;
        }

        for (int x = 1; x < shared_space[0]; x++)
        {
            printf("%c",shared_space[x]);
        }
        printf("\n\n");
        

        for (int i = 0; i < 26; i++)
        {
            SIGNAL[0].sem_num = i;
            semop(sem, SIGNAL, 1);
        }

        printf("Semaforo segnalato!\n");

        semop(sem2, WAIT, 1);

    }

    shared_space[0] = -1;
        
    fclose(file);
    shmdt(shared_space);
}

// ------------------------------------ S -----------------------------------------

void S(int msgQueue, int sem2) {
    LineStat line_stat;
    LineStat line_stats[26];
    LineStat line_stats_tot[26];
    struct sembuf SIGNAL[1] = { { 0, +1, 0 } };

    for (int i = 0; i < 26; i++)
    {
        line_stats_tot[i].occurrencies = 0;
    }
    

    //semop(sem2, SIGNAL, 1);

    while (1)
    {
        for (int i = 0; i < 26; i++)
        {
            if (msgrcv(msgQueue, &line_stat, sizeof(line_stat)-sizeof(long), 0, 0) == -1) {
                //perror("\n<< Errore >> : Impossibile ricevere messaggio dalla coda.\n");
                printf("\n\n------------- Final Stats ----------------\n\n");
                for (int i = 0; i < 26; i++)
                {
                    printf("Occorrenze di '%c' : %d\n", line_stats_tot[i].charNum, line_stats_tot[i].occurrencies);
                }
                printf("\n\n--------------------------------------------\n\n");
                exit(1);
            }

            //printf("Sono il processo S, numero di occorrenze di %c : %d\n", line_stat.charNum, line_stat.occurrencies);
            line_stats[i] = line_stat;
        }

        for (int i = 0; i < 26; i++)
        {
            for (int j = i; j < 26; j++)
            {
                if (line_stats[j].charNum < line_stats[i].charNum)
                {
                    LineStat tmp;
                    tmp = line_stats[i];
                    line_stats[i] = line_stats[j];
                    line_stats[j] = tmp;
                }   
            }
        }

        for (int i = 0; i < 26; i++)
        {
            printf("\n - Occorrennza di '%c' : %d\n", line_stats[i].charNum, line_stats[i].occurrencies);
            line_stats_tot[i].charNum = line_stats[i].charNum;
            line_stats_tot[i].occurrencies += line_stats[i].occurrencies;
        }

        semop(sem2, SIGNAL, 1);
    }
    

}

void F(int msgQueue, int shm_id, int sem, int charNum) {

    LineStat line_stat;
    line_stat.occurrencies = 0;
    
    struct sembuf WAIT_26[1] = { { 0, -1, 0 } };
    WAIT_26[0].sem_num = charNum;
    int *shared_space;

    if ((shared_space = (int *)shmat(shm_id, NULL, 0)) == (int *)-1) {
        perror("shmat");
        exit(1);
    }

    char myChar = (char)charNum + 65;
    int c_count = 1;

    while (shared_space[0] != -1)
    {   
        semop(sem, WAIT_26, 1);
        //printf("\nFiglio %d creato [ PID = %d ] [ Char: %c ]\n", charNum, getpid(), myChar);
        line_stat.charNum = (int) myChar;
        //printf("Shared_space[0] = %d\n", shared_space[0]);
        for (int i = 1; i < shared_space[0]; i++)
        {   
            //printf("is %c == %c \n", shared_space[i], myChar);
            if(toupper(shared_space[i]) == (int) myChar) line_stat.occurrencies++;
        }
        //printf("\n%d) [ Number of %c : %d ]\n", c_count, myChar, line_stat.occurrencies);
        
        msgsnd(msgQueue, &line_stat, sizeof(line_stat) - sizeof(long), 0);

        line_stat.occurrencies = 0;

        c_count++;
    }
    

    shmdt(shared_space);
    exit(1);
}

// ---------------------------------- MAIN -----------------------------------------------

int main(int argc, char const *argv[])
{
    // Zona di memoria condivisa
    int shm_id = shmget(IPC_PRIVATE, sizeof(char) * 1000, IPC_CREAT | 0600);
    if (shm_id == -1)
    {
        perror("\n\n<< Errore >> : Impossibile creare la zona di memoria condivisa.\n\n");
        exit(1);
    }

    // Primo semaforo
    int sem = semget(IPC_PRIVATE, 26, IPC_CREAT | 0600);
    if (sem == -1)
    {
        perror("\n\n<< Errore >> : Imposibile creare semaforo sem.\n\n");
        exit(1);
    }

    for (int i = 0; i < 26; i++)
    {
        if (semctl(sem, i, SETVAL, 0) == -1) {
            perror("\n\n<< Errore >> : Imposibile impostare semaforo sem a 0.\n\n");
            exit(1);
        }
    }

    // Secondo semaforo
    int sem2 = semget(IPC_PRIVATE, 1, IPC_CREAT | 0600);
    if (sem2 == -1) {
        perror("\n\n<< Errore >> : Imposibile creare semaforo sem2.\n\n");
        exit(1);
    }

    if (semctl(sem, 0, SETVAL, 0) == -1) {
        perror("\n\n<< Errore >> : Imposibile impostare semaforo sem a 0.\n\n");
        exit(1);
    }

    // Coda di messaggi
    int msgQueue = msgget(IPC_PRIVATE, IPC_CREAT | IPC_EXCL | 0660);
    if (msgQueue == -1) {
        perror("\n\n<< Errore >> : Impossibile creare coda di messaggi.\n\n");
        exit(1);
    }

    for (int j = 0; j < 26; j++)
    {   
        int pid = fork(); 
        if (pid != 0)
        {
            
        }
        else if (pid != -1)
        {

            F(msgQueue, shm_id, sem, j);

        }
        else printf("\n\n<< Errore >> : Impossibile creare figlio %d .\n\n", j);
    }

    int pid = fork();
    if (pid != 0){

    }
    else if (pid != -1){

        S(msgQueue, sem2);
        printf("\nS creato\n");
        exit(1);
    }
    else perror("\n\n<< Errore >> : Impossibile Creare figlio S.\n\n");

    P(shm_id, sem, sem2);

    
    if (semctl(sem, 26, IPC_RMID) == -1) perror("\n\n<< Errore >> : Impossibile rimuovere semaforo sem.\n\n");
    if (shmctl(shm_id,IPC_RMID, NULL) == -1) perror("\n\n<< Errore >> : Impossibile distruggere zona di memoria condivisa.\n\n");
    if (msgctl(msgQueue, IPC_RMID, NULL) == -1) perror("\n\n<< Error >> : Impossibile rimuovere la coda di messaggi.\n\n");

    return 0;
}



