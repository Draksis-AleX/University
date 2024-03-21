#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>

#define BUFFSIZE 128
#define PROCNAMESIZE 16

//usato per scambiare messaggi fra processi IN e DB
typedef struct{
    long type;
    char msg[BUFFSIZE];
    char processName[PROCNAMESIZE];
    int done;
}msgbuf;

typedef struct{
    char key[BUFFSIZE];
    int value;
}entry;

typedef struct{
    long type;
    char processName[PROCNAMESIZE];
    char key[BUFFSIZE];
    int value;
}outmsg;

void err(char *msg){
    perror(msg);
    exit(1);
}

void INProcess(char* filename, int msgq, char* processName){
    
    FILE *in;
    if( (in = fopen(filename, "r" )) == NULL ) err("fopen");

    //messaggio da mandare tramite coda
    msgbuf mess;
    mess.type = 1; //tipo di mesaggio della query
    strcpy(mess.processName, processName);
    mess.done = 0;

    int queryNum = 0;
    char buff[BUFFSIZE];

    while( fgets(buff, BUFFSIZE, in) ){

        queryNum++;
        if(buff[ strlen(buff)-1 ] == '\n') buff[ strlen(buff)-1 ] = '\0'; //elimina lo \n eccessivo

        strcpy(mess.msg, buff);

        //messaggio da mandare tramite msgq al processo DB
        if ( msgsnd(msgq, &mess, sizeof(msgbuf) - sizeof(long), 0) < 0 ) err("msgsnd"); 
        printf("%s: inviata query n.%d '%s'\n", processName, queryNum, buff);
    }
    //comunicare al processo DB che il processo IN ha finito di leggere le query
    mess.done = 1;
    if ( msgsnd(msgq, &mess, sizeof(msgbuf) - sizeof(long), 0) < 0 ) err("msgsnd"); 
    fclose(in);
    exit(0);
}


int getLineCount(char *filename){
    FILE *in;
    if ( (in = fopen(filename, "r")) == NULL) err("fopen");
    int lines = 0;
    char buff[BUFFSIZE];
    while( fgets(buff, BUFFSIZE, in) ) lines++;
    fclose(in);
    return lines;
}

//usa malloc per allocare il file DB in memoria sottoforma di array di entries
entry *loadInMem(char *filename, int size){

    FILE *in;
    if ( (in = fopen(filename, "r")) == NULL ) err("fopen");
    //alloca l'array di entries in memoria
    entry *entries = malloc(size * sizeof(entry));

    //RIEMPIRE l'ARRAY DI ENTRIES
    char buff[BUFFSIZE];
    for(int i=0; i<size; i++ ){
        fgets(buff, BUFFSIZE, in);
        //entries[i].key = (char*) malloc(sizeof(char*));
        strcpy(entries[i].key, strtok(buff, ":") );
        entries[i].value = atoi(strtok(NULL, "\n"));
    }

    fclose(in);
    return entries;

}

int findValue(entry *entries, int size, char* query){
    for(int i=0; i<size; i++)
        if( strcmp(entries[i].key, query) == 0 ) return entries[i].value;
    return -1;
}

void DBProcess(int msgIN, int msgOUT, char *filename){

    int size = getLineCount(filename);
    entry *entries = loadInMem(filename, size);
    printf("DB: caricati %i elementi in memoria\n", size);

    //leggi i messaggi mandati da IN1 ed IN2
    int foundValue;
    int processStop = 0; //DB si ferma quando questo valore raggiunge 2
    char buff[BUFFSIZE];
    msgbuf mess;
    outmsg outmess;
    outmess.type = 1;
    while(1){
        if (msgrcv(msgIN, &mess, sizeof(msgbuf) - sizeof(long), 0, 0) < 0) err("msgrcv");

        //controlliamo se è un messaggio di stop
        if(mess.done){
            processStop++;
            if(processStop == 2) break;
            else continue;
        }

        if ( (foundValue = findValue(entries, size, mess.msg)) >= 0 ){
            printf("DB: query '%s' da %s trovata con valore %i\n", mess.msg, mess.processName, foundValue);
            //bisogna mandare un messaggio ad OUT utilizzando la coda msgOUT
            strcpy(outmess.processName, mess.processName);
            strcpy(outmess.key, mess.msg);
            outmess.value = foundValue;
            if( msgsnd(msgOUT, &outmess, sizeof(outmsg) - sizeof(long), 0) < 0 ) perror("msgsnd");    
        }else{
            printf("DB: query '%s' da %s non trovata\n", mess.msg, mess.processName);
        }
    }

    //usciti dal while contattiamo il processo OUT
    outmess.value = -1;
    if( msgsnd(msgOUT, &outmess, sizeof(outmsg) - sizeof(long), 0) < 0 ) perror("msgsnd");

    //free dell'array entries
    free(entries);
    exit(0);
}



void OUTProcess(int msgq){
    outmsg mess;
    int IN1val = 0, IN1validQueries=0, IN2val = 0, IN2validQueries=0;

    while(1){
        if (msgrcv(msgq, &mess, sizeof(outmsg) - sizeof(long), 0, 0) < 0) err("msgrcv");

        //controlla se è il messaggio di stop
        if( mess.value < 0 ) break;
    
        if( strncmp("IN1", mess.processName, 3) == 0 ){
            IN1val += mess.value;
            IN1validQueries++;
        }else{
            IN2val += mess.value;
            IN2validQueries++;
        }

    }

    printf("OUT: ricevuti n.%i valori validi per IN1 con totale %i\n", IN1validQueries, IN1val);
    printf("OUT: ricevuti n.%i valori validi per IN2 con totale %i\n", IN2validQueries, IN2val);
    exit(0);
}

//PROCESSO P
int main(int argc, char *argv[]){
    
    
    if( argc != 4 ){
        fprintf(stderr, "sintassi errata.\n");
        exit(1);
    }

    int msgIN; //coda che viene utilizzata dai processi IN1, IN2 e DB
    if ( ( msgIN = msgget(IPC_PRIVATE, IPC_CREAT | IPC_EXCL | 0660 ) ) < 0 ) err("msgget");

    int msgOUT; //coda che viene utilizzata dai processi DB ed OUT
    if ( ( msgOUT = msgget(IPC_PRIVATE, IPC_CREAT | IPC_EXCL | 0660 ) ) < 0 ) err("msgget");

    //CREAZIONE PROCESSI

    //DB
    if( fork() == 0 ) DBProcess(msgIN, msgOUT, argv[1]);

    //IN1
    if( fork() == 0 ) INProcess(argv[2], msgIN, "IN1");
    
    //IN2
    if( fork() == 0 ) INProcess(argv[3], msgIN, "IN2");
    
    //OUT
    if( fork() == 0) OUTProcess(msgOUT);
    
    for(int i=0; i<4; i++) wait(NULL);

    msgctl(msgIN, IPC_RMID, NULL); //cancella la coda msgIN
    msgctl(msgOUT, IPC_RMID, NULL); //cancella la coda msgOUT


    return 0;
    
}