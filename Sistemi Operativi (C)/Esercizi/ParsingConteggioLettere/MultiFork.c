
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <sys/sem.h>

int counter = 0;

int main(int argc, char const *argv[])
{
    printf("\nCiao %d [%d]\n", counter, getpid());

    int j = 0;

    while(j < 3){

        if (fork() == 0)
        {
            printf("\nSono il figlio %d [%d]\n", j, getpid());
            exit(1);
        }
        j++;
    }
    for (int i = 0; i < 3; i++)
    {
        wait(NULL);
    }

    if(fork() == 0) {
        printf("\n\nNew Child after while");
    }
    
    exit(1);
    return 0;
}
