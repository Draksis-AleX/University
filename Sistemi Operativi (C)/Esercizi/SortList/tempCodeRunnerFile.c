#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <sys/sem.h>
#include <stdio.h>

#include <sys/mman.h>
#include <sys/stat.h>

#define MAX_WORLD_LEN 50

typedef struct{
    long mtype;
    char*line;
}msg;

typedef struct{
    long mtype;
    short flag;
}ris;

typedef struct{
    long mtype;
    char line1[MAX_WORLD_LEN];
    char line2[MAX_WORLD_LEN];
}cmp;

void Sorter(int msg_id,char* path){

    printf("\x1b[32m[S] avvio \x1b[0m \n");

    FILE* file;
    struct stat df;

    if((file=fopen(path,"r")) == NULL){
        perror("errore aoertura file");
        exit(1);
    }

    char line[MAX_WORLD_LEN];

    int n_righe=0;

    while(fgets(line, MAX_WORLD_LEN ,file)){
        //printf("\x1b[32m[S] RIGHE %s\x1b[0m\n",line);
        n_righe++;
    }

    char unsort[n_righe][MAX_WORLD_LEN];
    int x=0;

    printf("\x1b[32m[S] RIGHE %d\x1b[0m\n",n_righe);

    if(fseek(file,0,SEEK_SET)){
        perror("fseek");
        exit(1);
    }

    while(fgets(line, MAX_WORLD_LEN ,file)){
       strncpy(unsort[x],line, MAX_WORLD_LEN);
       //printf("\x1b[32m[S] RIGHE %s\x1b[0m\n",unsort[x]);
       x++;
    }

    //riordino

    char back[MAX_WORLD_LEN];

    ris rcv;
    cmp snd;

    rcv.mtype=1;
    snd.mtype=2;

    for (int i = 0; i < n_righe - 1; i++){

        for (int j = 0; j < n_righe - i - 1; j++) {

            strncpy(snd.line1,unsort[j],MAX_WORLD_LEN);
            strncpy(snd.line2,unsort[j+1],MAX_WORLD_LEN);

            //printf("\x1b[32m[%s - %s]  [dim %lu]\x1b[0m\n",snd.line1,snd.line2,sizeof(snd));

            if(msgsnd(msg_id,&snd, sizeof(snd) - sizeof(long),2) == -1){
                perror("msgsnd -s1");
                exit(1);
            }

            if(msgrcv(msg_id,&rcv,sizeof(rcv) - sizeof(long),1,0) == -1){
                perror("msgrcv -s2");
                exit(1);
            }

            printf("swap %d - %d\n",i,j);

            if (rcv.flag) {
                strcpy(back,unsort[j]);
                strcpy(unsort[j],unsort[j+1]);
                strcpy(unsort[j+1],back);
            }
        
        }

    }

    strcpy(snd.line1,"?la vera?");
    strcpy(snd.line2,"?lfine?");
    
    if(msgsnd(msg_id,&snd,sizeof(snd) - sizeof(long),2) == -1){
        perror("msgsnd -s");
        exit(1);
    }

    msg messaggio;
    messaggio.mtype=3;

    for(int i =0 ; i<0; i++){
        strncpy(messaggio.line,unsort[i],MAX_WORLD_LEN);
        if(msgsnd(msg_id,&messaggio,sizeof(messaggio) - sizeof(long),3) == -1){
            perror("msgsnd -s");
            exit(1);
        } 
    }

    printf("\nqui\n");

    strncpy(messaggio.line,"?la vera?",MAX_WORLD_LEN);

    if(msgsnd(msg_id,&messaggio,sizeof(messaggio) - sizeof(long),3) == -1){
        perror("msgsnd -s");
        exit(1);
    }

    

    exit(0);
    
}

void Comparer(int msg_id){

    printf("[C] avvio \n");

    ris snd;
    cmp rcv;

    rcv.mtype=2;
    snd.mtype=1;

    while(1){

        if(msgrcv(msg_id,&rcv,sizeof(rcv) - sizeof(long),2,0) == -1){
            perror("msgrcv -c");
            exit(1);
        }

        if(strcmp(rcv.line1,"?la vera?")==0 && strcmp(rcv.line2,"?fine?")==0) break;

        printf("C - messaggio revuto");

        //printf("l1 %s - l2 %s\n",rcv.line1,rcv.line2);
    
        if(strcasecmp(rcv.line1,rcv.line2)>0) snd.flag=1;
        else snd.flag=0;

        if(msgsnd(msg_id,&snd,sizeof(snd) - sizeof(long),0) == -1){
            perror("msgsnd -c");
            exit(1);
        }
    }
    

    printf("[C] fine \n");
    exit(0);
}

void P(int msg_id){
    
    int len;
    msg messaggio;
    messaggio.mtype=3;

    strncpy(messaggio.line,"",MAX_WORLD_LEN);

    while(strcmp(messaggio.line,"?la vera?")!=0){
         if ((len = msgrcv(msg_id, &messaggio, sizeof(messaggio) - sizeof(long), 3,0)) == -1) {
            perror("msgrcv");
            exit(1);
        } 
        printf("[P] %s\n",messaggio.line);
    }

}


int main(){

    char* path="text.txt";

    printf("[P] avvio \n");

    //creazione coda di messaggi 

    int msgId;

    if((msgId= msgget(IPC_PRIVATE,IPC_CREAT | 0660)) == -1){
        perror("errore creazione coda di messaggi");
        exit(1);
    }

    //creazione processi figli 

    int pid= fork();

    if(pid==0){
        Sorter(msgId,path);

    }
    else if(pid == -1){
        perror("errore fork Sorter");
        exit(1);

    }

    pid = fork();


    if(pid==0){
        Comparer(msgId);

    }
    else if(pid == -1){
        perror("errore fork Comparer");
        exit(1);

    }


    P(msgId);

    for (int i = 0; i < 2; i++) wait(NULL);


    //rimozione ipc 

    msgctl(msgId,IPC_RMID,NULL);
    printf("[P] fine \n");
    
    return(0);

}


