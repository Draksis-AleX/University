#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <sys/sem.h>

#define MAX_WORD_LEN 50

typedef struct{
    long type;
    char word[MAX_WORD_LEN];
    int done;
} fmsg;

typedef struct{
    long type;
    char word_i[MAX_WORD_LEN];
    char word_j[MAX_WORD_LEN];
    int done;
} cmp;

typedef struct{
    long type;
    int ris;
} res;

void error(char* msg){
    printf("\n\n\x1b[31m<< Errore >>\n\t");
    perror(msg);
    printf("\x1b[0m\n");
    exit(1);
}

void SIGNAL(int sem_s){
    struct sembuf op[1] = {0, +1, 0};
    semop(sem_s, op, 1);
}

void WAIT(int sem_s){
    struct sembuf op[1] = {0, -1, 0};
    semop(sem_s, op, 1);
}

int countLines(char* filename){
    FILE* file = fopen(filename, "r");
    int n = 0;
    char buff[MAX_WORD_LEN];

    while (fgets(buff, MAX_WORD_LEN, file)) n++;

    fclose(file);

    return n;
}

void printArray(char** array, int n){

    for (int i = 0; i < n; i++)
    {
        printf("- %s\n", array[i]);
    }

}

//-------------------------------  SORTER  ------------------------------------

void sorter(int msg_id, char* filename){
    printf("\n[[SORTER]] : Sono stato creato.\n");

    FILE* text_file = fopen(filename, "r");

    int n_words = countLines(filename);

    printf("\n[[SORTER]] : Words number = %d\n", n_words);

    char* words[n_words];
    char word[MAX_WORD_LEN];
    int i = 0;
    while (fgets(word, MAX_WORD_LEN, text_file))
    {   
        words[i] = malloc((MAX_WORD_LEN+1)*sizeof(char));
        strcpy(words[i], word);
        i++;
    }
    printf("\n[[SORTER]] : Unsorted Array:\n");
    printArray(words, n_words);

    fclose(text_file);

    cmp msgcmp;
    msgcmp.done = 0;
    msgcmp.type = 1;

    res result;
    result.type = 1;

    for (int i = 0; i < n_words - 1; i++)
    {
        for (int j = i + 1; j < n_words; j++)
        {
            strcpy(msgcmp.word_i, words[i]);
            strcpy(msgcmp.word_j, words[j]);

            if(i == n_words - 2 && j == n_words - 1) msgcmp.done = 1;
            if(msgsnd(msg_id, &msgcmp, sizeof(cmp) - sizeof(long), 0) < 0)
                error("Sorter: Impossibile inviare messaggio.\n");
            
            if(msgrcv(msg_id, &result, sizeof(res) - sizeof(long), 2, 0) < 0)
                error("Sorter: Impossibile ricevere messaggio.\n");
            
            if(result.ris == 1){
                char app[MAX_WORD_LEN];
                strcpy(app, words[i]);
                strcpy(words[i], words[j]);
                strcpy(words[j], app);
            }
        }
    }
    
    //printArray(words, n_words);ù

    fmsg father_msg;
    father_msg.type = 3;
    father_msg.done = 0;

    for (int i = 0; i < n_words; i++)
    {
        strcpy(father_msg.word, words[i]);
        if(i == n_words - 1) father_msg.done = 1;
        if(msgsnd(msg_id, &father_msg, sizeof(fmsg) - sizeof(long), 0) == -1)
            error("Sorter: Impossibile inviare messaggio al padre.\n");
    }
    
    exit(0);
}

//-----------------------------------------------------------------------------

//------------------------------  COMPARER  -----------------------------------

void comparer(int msg_id){
    printf("\n[[COMPARER]] : Sono stato creato.\n");

    cmp msgcmp;
    res result;
    result.type = 2;
    result.ris = 0;

    while (1)
    {
        if(msgrcv(msg_id, &msgcmp, sizeof(cmp) - sizeof(long), 1, 0) < 0)
            error("Comparer: Impossibile ricevere messaggio.\n");

        //printf("\n[[COMPARER]] : Word[i] = %s, Word[j] = %s\n", msgcmp.word_i, msgcmp.word_j);

        if (strcasecmp(msgcmp.word_i, msgcmp.word_j) > 0)
            result.ris = 1;
        else result.ris = 0;

        if(msgsnd(msg_id, &result, sizeof(res) - sizeof(long), 0) < 0)
            error("Comparer: Impossibile inviare messaggio.\n");
        
        if(msgcmp.done == 1) break;
    }

    printf("\n[[COMPARER]] : Ho finito.\n");

    exit(0);
}

//-----------------------------------------------------------------------------

//--------------------------------  P  ----------------------------------------

void P(int msg_id){

    fmsg father_msg;

    while (1)
    {
        if(msgrcv(msg_id, &father_msg, sizeof(fmsg) - sizeof(long), 3, 0) == -1)
            error("Padre: Impossibile ricevere messaggio.\n");
        printf("- %s\n", father_msg.word);
        if(father_msg.done == 1) break;
    }
    
}

//-----------------------------------------------------------------------------

//-------------------------------  MAIN  --------------------------------------

int main(int argc, char const *argv[])
{

    char* filename = "text.txt";

    //---------------  DICHIARAZIONE IPC  -----------------

    int msg_id;
    if((msg_id = msgget(IPC_PRIVATE, IPC_CREAT | IPC_EXCL | 0660)) < 0)
        error("Impossibile creare coda di messaggi\n");

    //-------------- CREAZIONE FIGLI  ---------------------z

    int pid_sorter = fork();
    if(pid_sorter == 0) sorter(msg_id, filename);

    int pid_comparer = fork();
    if(pid_comparer == 0) comparer(msg_id);

    P(msg_id);

    for (int i = 0; i < 2; i++)
    {
        wait(NULL);
    }

    //---------------  DISTRUZIONE IPC  -------------------

    if(msgctl(msg_id, IPC_RMID, NULL) == -1)
        error("Impossibile distruggere coda di messaggi.\n");

    return 0;
}
