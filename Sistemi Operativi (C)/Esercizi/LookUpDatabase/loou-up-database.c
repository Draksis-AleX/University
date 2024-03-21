#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>

#define BUFFSIZE 128
#define PROCNAMESIZE 16

void error(char* msg) {
    perror(msg);
    exit(1);
};

int getLineCount(char *filename){
    FILE *in;
    if ( (in = fopen(filename, "r")) == NULL) error("fopen");
    int lines = 0;
    char buff[BUFFSIZE];
    while( fgets(buff, BUFFSIZE, in) ) lines++;
    fclose(in);
    return lines;
};

typedef struct {
    char name[BUFFSIZE];
    int value;
} entry;

typedef struct {
    long type;
    char process[16];
    char name[BUFFSIZE];
} query_msg;

typedef struct {
    long type;
    char process[16];
    int value;
} out_msg;

void INProcess(int msg_queue, char* processName, char* fileName){

    printf("\n%s creato.\n", processName);

    FILE *query_file = fopen(fileName, "r");
    
    query_msg msg;
    msg.type = 1;
    strcpy(msg.process, processName);
    int queryNum = 0;

    char name[BUFFSIZE];

    while (fgets(name, BUFFSIZE, query_file))
    {
        
        if(name[ strlen(name)-1 ] == '\n') name[ strlen(name)-1 ] = '\0'; //elimina lo \n eccessivo
        strcpy(msg.name, name);

        if ( msgsnd(msg_queue, &msg, sizeof(query_msg) - sizeof(long), 0) < 0 ) error("msgsnd");
        printf("%s: inviata query n.%d '%s'\n", processName, queryNum++, name);
    }
    
    strcpy(msg.name, "!-abort-!");
    if ( msgsnd(msg_queue, &msg, sizeof(query_msg) - sizeof(long), 0) < 0 ) error("msgsnd");
    fclose(query_file);
    printf("\nIN process died.\n");

}

entry* loadInMem(char *filename, int size){

    FILE *file = fopen(filename, "r");
    char line[BUFFSIZE];
    
    entry* database = malloc(sizeof(entry) * size);

    int i = 0;
    while (fgets(line, sizeof(entry), file))
    {
        //printf("\nLine : %s\n", line);

        entry new_entry;
        strcpy(new_entry.name, strtok(line, ":"));
        new_entry.value = atoi(strtok(NULL, "\n"));

        database[i++] = new_entry;

        printf("\nNew DB Entry -- Name : %s, Value : %d\n", database[i-1].name, database[i-1].value);
    }

    fclose(file);
    return database;

}

void DB(int msg_queue, int msg_queue_out){

    printf("\nDB creato.\n");

    //-----------------------Caricamento file in memoria------------------------------------------

    int size = getLineCount("database.txt");
    entry* database = loadInMem("database.txt", size);

    //----------------------------------Ricerca------------------------------------------------
    
    query_msg msg;
    out_msg msgo;
    msgo.type = 1;
    int abort_counter = 0;

    while(1){

        if(msgrcv(msg_queue, &msg, sizeof(query_msg) - sizeof(long), 0, 0) < 0)
            error("\n\n<< Errore >> : Impossibile ricevere per DB.\n\n");

        if(strcmp(msg.name, "!-abort-!") == 0) abort_counter++;
        if(abort_counter >= 2) break;

        printf("\nNew msg\n\t>> %s: %s", msg.process, msg.name);

        for (int i = 0; i < size; i++)
        {   
            if(strcmp(msg.name, database[i].name) == 0){
                
                strcpy(msgo.process, msg.process);
                msgo.value = database[i].value;
                printf("\nSending message to out\n");
                if (msgsnd(msg_queue_out, &msgo, sizeof(out_msg) - sizeof(long), 0) < 0 )
                    error("\n\n<< Errore >> : Impossibile inviare messaggio ad OUT\n");
            }
        }
    }
    
    printf("\nSearching aborted\n");

    strcpy(msgo.process, "!-Abort-!");
    msgo.value = -1;
    if(msgsnd(msg_queue_out, &msgo, sizeof(out_msg) - sizeof(long), 0) < 0) error("\n\n<< Errore >> : Impossibile mandare messaggio terminale ad out.\n\n");
    free(database);
}

void OUT(int msg_queue_out){
    out_msg msgout;
    int in1_tot = 0, in2_tot = 0, in1_check_count = 0, in2_check_count = 0;

    while (1)
    {
        if (msgrcv(msg_queue_out, &msgout, sizeof(out_msg) - sizeof(long), 0, 0) < 0)
            error("\n\n<< Errore >> : Impossibile ricevere messaggi per OUT.\n\n");

        if((strcmp(msgout.process, "!-Abort-!") == 0) && msgout.value < 0) break;

        if(strcmp(msgout.process, "IN1") == 0){
            in1_check_count++;
            in1_tot += msgout.value;
        }
        else if(strcmp(msgout.process, "IN2") == 0){
            in2_check_count++;
            in2_tot += msgout.value;
        }
    }

    printf("\n\n[ FINAL RESULTS ]\n\n");
    printf("[IN1]\n\tNomi trovati : %d\n\tTotale : %d\n\n", in1_check_count, in1_tot);
    printf("[IN2]\n\tNomi trovati : %d\n\tTotale : %d\n\n", in2_check_count, in2_tot);    

}

int main(int argc, char const *argv[])
{

    //-----------------------------Dichiarazione IPC----------------------------------------

    int msgIN; //coda che viene utilizzata dai processi IN1, IN2 e DB
    if ( ( msgIN = msgget(IPC_PRIVATE, IPC_CREAT | IPC_EXCL | 0660 ) ) < 0 ) error("msgget");

    int msgOUT; //coda che viene utilizzata dai processi DB ed OUT
    if ( ( msgOUT = msgget(IPC_PRIVATE, IPC_CREAT | IPC_EXCL | 0660 ) ) < 0 ) error("msgget");

    //------------------------------Creazione figli-----------------------------------------
    int pid_db = fork();
    if(pid_db == 0) {      //Corpo figlio
        DB(msgIN, msgOUT);
        exit(0);
    }
    else if(pid_db == -1) error("\n\n<< Errore >> : Impossibile creare DB.\n\n");

    int pid_in1 = fork();
    if(pid_in1 == 0) {      //Corpo figlio
        INProcess(msgIN, "IN1", "query1.txt");
        exit(0);
    }
    else if(pid_in1 == -1) error("\n\n<< Errore >> : Impossibile creare IN1.\n\n");

    int pid_in2 = fork();
    if(pid_in2 == 0) {      //Corpo figlio
        INProcess(msgIN, "IN2", "query2.txt");
        exit(0);
    }
    else if(pid_in2 == -1) error("\n\n<< Errore >> : Impossibile creare IN2.\n\n");

    int pid_out = fork();
    if(pid_out == 0) {      //Corpo figlio
        OUT(msgOUT);
        exit(0);
    }
    else if(pid_out == -1) error("\n\n<< Errore >> : Impossibile creare OUT.\n\n");

    //----------------------------Attesa fine figli----------------------------------------

    for (int i = 0; i < 4; i++)
    {
        if(wait(NULL) == -1) error("\n\n<< Errore >> : Impossibile aspettare figli.\n\n");
    }
    
    //---------------------------Distruzione IPC------------------------------------------

    if(msgctl(msgIN, IPC_RMID, NULL) == -1) error("\n\n<< Errore >> : Impossibile distruggere coda di messaggi.\n\n");
    if(msgctl(msgOUT, IPC_RMID, NULL) == -1) error("\n\n<< Errore >> : Impossibile distruggere coda di messaggi OUT.\n\n");

    return 0;
}
