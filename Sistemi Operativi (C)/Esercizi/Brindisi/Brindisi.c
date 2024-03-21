/*
 ============================================================================
 Name        : 2020-assignment-buddies.c
 Author      : PT
 Version     :
 Copyright   : For personal use only. Please do not redistribute
 Description : Template for semaphore assignment summer 2020
 ============================================================================
 */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/sem.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>

#define FOREVER while(!time_up)
#define GROUP_SIZE 5

/* the following values are just examples of the possible duration
 * of each action and of the simulation: feel free to change them */
#define N_THREADS 19
#define REFILL_TIME 5
#define MINGLE_TIME 12
#define END_OF_TIME 25

typedef char name_t[20];
typedef enum {FALSE, TRUE} boolean;


typedef struct 
{
    name_t thread_name;
    int sem_toasting;
} args;

time_t big_bang;
boolean time_up=FALSE;

void error(char* err){
    printf("\n%s\n", err);
    perror("\n");
    exit(1);
}

void WAIT(sem, n){
    struct sembuf op[1] = {{n, -1, 0}};
    semop(sem, op, 1);
}

void SIGNAL(sem, n){
    struct sembuf op[1] = {{n, +1, 0}};
    semop(sem, op, 1);
}

// GLOBAL VARS, TYPE DEFS ETC

void wait_for_toasting() {
    

}

void wait_for_drinking() {
    // YOUR CODE HERE
}

void do_action(char *thread_name, char *action_name, int max_delay) {
    printf("\x1b[31mThread %s : %s\x1b[0m", thread_name, action_name);
    int delay=rand()%max_delay+1;
    sleep(delay);
}

void *buddy(void *thread_name, int sem_toasting) {
    int id=((char *)thread_name)[0]-'A';
    // LOCAL VARS ETC
    printf("%s joined the party\n", (char*) thread_name);
    FOREVER {
        do_action(thread_name, "go refill glass", REFILL_TIME);
        wait_for_toasting();
        if(!time_up)
            printf("[%4.0f]\t%s: Skol!\n", difftime(time(NULL),big_bang), (char*)thread_name);
        wait_for_drinking();
        if(!time_up) {
            printf("[%4.0f]\t%s drinks\n", difftime(time(NULL),big_bang), (char*) thread_name);
            do_action(thread_name, "drink and mingle", MINGLE_TIME);
            // UPDATE STATISTICS?
        }
    }
    printf("%s left the party\n", (char*) thread_name);
    pthread_exit(NULL);
}

int main(void) {
    int i;
    pthread_t tid[N_THREADS];
    name_t thread_name[N_THREADS] = {"Ali","Burhan","Cristina","Daniele",
    "Enrica","Filippo","Girish","Heidi","Ivan","Jereney","Kathy","Luca",
    "Mehran", "Nick", "Orazio", "Prem", "Quentin", "Reza", "Saad"};

    //======================== INITIALIZAION ==========================================

    int sem_toasting = semget(IPC_PRIVATE, 1, IPC_CREAT | 0600);
    if(sem_toasting == -1) error("Impossibile creare sem_toasting.\n");
    if(semctl(sem_toasting, 0, SETVAL, 0) == -1) error("Impossibile settare a 0 sem_toasting.\n");

    time(&big_bang);
    //================================================================================

    puts("\nWELCOME BUDDIES\n");

    args *th_args = (args *)malloc(sizeof(args));

    for(i=0;i<N_THREADS;i++) {
        strcpy(th_args->thread_name, thread_name[i]);
        th_args->sem_toasting = sem_toasting;
        pthread_create(&tid[i],NULL,buddy,(void*) th_args);
    }

    sleep(END_OF_TIME);
    time_up=TRUE;
    // UNLOCK WAITING THREADS?

    for(i=0;i<N_THREADS;i++) {
        pthread_join(tid[i],NULL);
        // UPDATE STATISTICS?
    }

    printf("\nParty statistics.\n- The most sober participant was %s, had only %d glasses :(\n- The thirstiest was %s. That party animal drunk as many as %d glasses B)\n",
            thread_name[0], 2,
            thread_name[1], 7);
    puts("\nGOODNIGHT BUDDIES\n");
    return EXIT_SUCCESS;
}
