#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

sem_t s_a_concluded, s_b_concluded;


void *f_a(void *arg) {
     sleep(3);
    puts("!!!First Hello World!!!");
    sem_post(&s_a_concluded);
    return NULL;
}

void *f_b(void *arg) {
    sem_wait(&s_a_concluded);
    puts("!!!Second Hello World!!!");
    sem_post(&s_b_concluded);
    return NULL;
}

int main(void) {
    pthread_t thread_a, thread_b;

    // this is a good place to init semaphores

    sem_init(&s_a_concluded,0,0);
    sem_init(&s_b_concluded,0,0);

    pthread_create(&thread_a, NULL, f_a, NULL);
    pthread_create(&thread_b, NULL, f_b, NULL);

    // sleep(1);
    sem_wait(&s_b_concluded);
    puts("!!!Third Hello World!!!");

    pthread_join(thread_a,NULL);
    pthread_join(thread_b,NULL);

    sem_destroy(&s_a_concluded);
    sem_destroy(&s_b_concluded);

    puts("!!!Last Hello World!!!");
    return EXIT_SUCCESS;
}
