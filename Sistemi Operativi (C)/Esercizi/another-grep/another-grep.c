#include <unistd.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

#define MAX_LINE_LEN 1024

typedef struct{
    long type;
    char line[MAX_LINE_LEN];
    int done;
} queue_msg;

void error(char* msg){
    printf("\n\n\x1b[31m<<Errore>>\n\t");
    perror(msg);
    printf("\x1b[0m\n");
    exit(1);
}

//-----------------------------------  W  -------------------------------------

void W(int msg_id){
    printf("\x1b[32m[W] : Sono stato creato.\x1b[0m\n");
    queue_msg msg;
    while (1)
    {
        if(msgrcv(msg_id, &msg, sizeof(queue_msg) - sizeof(long), 0, 0) < 0) error("[W] : msgrcv\n");
        if(msg.done == 1) break;

        printf("\x1b[32m[W] : Ho ricevuto : %s.\x1b[0m\n", msg.line);
    }
    
    printf("\x1b[32m[W] : Ho finito.\x1b[0m\n");

    exit(0);
}

//-----------------------------------------------------------------------------

//-----------------------------------  R  -------------------------------------

void R(int pipe_id[], char* filename){
    printf("\x1b[33m[R] : Sono stato creato.\x1b[0m\n");

    int fd = open(filename, O_RDONLY);

    struct stat file_stat; 
    if(fstat(fd, &file_stat) == -1) error("Impossibile ottenere stats del file.\n");

    char* mapped_file = (char*) mmap(NULL, file_stat.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    if(mapped_file == MAP_FAILED) error("Impossibile mappare il file in memoria.\n");

    printf("\x1b[33m[R] : File mappato in memoria:\n%s\x1b[0m\n", mapped_file);

    close(pipe_id[0]);
    
    write(pipe_id[1], mapped_file, file_stat.st_size);

    //printf("\x1b[33m[R] : Ho finito\x1b[0m\n");

    close(pipe_id[1]);

    munmap(mapped_file, file_stat.st_size);
    close(fd);
    exit(0);
}

//-----------------------------------------------------------------------------

//-----------------------------------  P  -------------------------------------

void P(int pipe_id[], int msg_id, char* word){

    close(pipe_id[1]);
    FILE* pipe_file = fdopen(pipe_id[0], "r");
    int control = 0;
    
    char line[MAX_LINE_LEN];
    while (fgets(line, MAX_LINE_LEN, pipe_file))
    {
        //printf("[P] : Line = %s\n", line);
        if(strcasestr(line, word) != NULL){
            queue_msg msg;
            msg.type = 1;
            msg.done = 0;
            strcpy(msg.line, line);
            if(msgsnd(msg_id, &msg, sizeof(queue_msg) - sizeof(long), 0) < 0) error("[P] : msgsnd\n");
        }
    }
    

    close(pipe_id[0]);

    queue_msg msg;
    msg.type = 1;
    msg.done = 1;
    strcpy(msg.line, "--end--");
    if(msgsnd(msg_id, &msg, sizeof(queue_msg) - sizeof(long), 0) < 0) error("[P] : msgsnd\n"); 
    
    printf("[P] : finito.\n");

}

//-----------------------------------------------------------------------------

//-----------------------------------  MAIN  ----------------------------------

int main(int argc, char const *argv[])
{
    
    const char* filename = argv[1];
    const char* word = argv[2];

    //------------------  DICHIARAZIONE IPC  --------------

    int pipe_id[2];
    if(pipe(pipe_id) == -1) error("Impossibile creare pipe.\n");

    int msg_id = msgget(IPC_PRIVATE, IPC_CREAT | IPC_EXCL | 0660);
    if(msg_id == -1) error("Impossibile creare coda di messaggi.\n");

    //-----------------------------------------------------

    //-----------------  CREAZIONE FIGLI  -----------------

    int pid_r = fork();
    if(pid_r == 0){
        close(pipe_id[0]);
        R(pipe_id, filename);
    } 

    int pid_w = fork();
    if(pid_w == 0){
        close(pipe_id[1]);
        close(pipe_id[0]);
        W(msg_id);
    } 

    close(pipe_id[1]);
    P(pipe_id, msg_id, word);

    for (int i = 0; i < 2; i++) wait(NULL);
    
    //-----------------------------------------------------

    //----------------  DISTRUZIONE IPC  ------------------

    if(msgctl(msg_id, IPC_RMID, NULL) < 0) error("Impossibile distruggere coda di messaggi.\n");

    return 0;
}

//-----------------------------------------------------------------------------