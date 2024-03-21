#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>

#define DIM_MSG 1024
typedef struct {
    long mtype;
    char mtext[DIM_MSG];
} msg;


int main() {
    int ds_coda, len;
    msg messaggio;
    if ((ds_coda = msgget(IPC_PRIVATE, IPC_CREAT | IPC_EXCL | 0660)) == -1) {
        perror("msgget");
        exit(1);
    }

    if (fork() == 0)
    {
        messaggio.mtype = 1;
        strncpy(messaggio.mtext, "Hello world!", DIM_MSG);
        if (msgsnd(ds_coda, &messaggio, sizeof(msg) - sizeof(long), IPC_NOWAIT) ==
            -1) {
            perror("msgsnd");
            exit(1);
        }
        strncpy(messaggio.mtext, "CANCELLO IL MESSAGGIO DAL BUFFER", DIM_MSG);
        exit(0);
    }
    
    if (fork() == 0)
    {
        if ((len = msgrcv(ds_coda, &messaggio, sizeof(messaggio) - sizeof(long), 0, 0)) ==
            -1) {
            perror("msgrcv");
            exit(1);
        } else {
            printf("Messaggio letto: '%s' (%d byte)\n", messaggio.mtext, len);
        }
        exit(0);
    }
    

    // crea ed invia il messaggio
    
    // legge esso stesso il messaggio
    
    // chiudo la coda
    msgctl(ds_coda, IPC_RMID, NULL);
}
