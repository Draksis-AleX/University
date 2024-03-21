
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

int main(int argc, char const *argv[])
{
    int sem = semget(IPC_PRIVATE, 3, IPC_CREAT | 0600);

    for (int i = 0; i < 3; i++)
    {
        semctl(sem, i, SETVAL, 0);
    }

    if(fork() == 0) {
        struct sembuf WAIT[1] = { { 0, -1, 0 } };
        semop(sem, WAIT, 1);

        printf("\nSono il figlio A\n");

        exit(0);

    }

    if(fork() == 0) {
        struct sembuf WAIT[1] = { { 1, -1, 0 } };
        semop(sem, WAIT, 1);

        printf("\nSono il figlio B\n");

        exit(0);

    }

    if(fork() == 0) {
        struct sembuf WAIT[1] = { { 2, -1, 0 } };
        semop(sem, WAIT, 1);

        printf("\nSono il figlio C\n");

        exit(0);

    }

    getchar();
    for (int i = 0; i < 3; i++)
    {
        struct sembuf SIGNAL[1] = { { i, +1, 0 } };
        semop(sem, SIGNAL, 1);
    }

    for (int i = 0; i < 3; i++)
    {
        if (wait(NULL) == -1) perror("\n\n<< Errore >> : Impossibile eseguire wait.\n\n");
    }
    

    printf("Suca");

    return 0;
}
