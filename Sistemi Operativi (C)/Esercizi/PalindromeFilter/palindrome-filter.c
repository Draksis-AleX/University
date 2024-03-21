#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <dirent.h>
#include <fcntl.h>

#define MAX_WORD_SIZE 36

void error(char* msg){
    printf("\n\n\x1b[31m << Errore >>\n\t");
    perror(msg);
    printf("\x1b[0m\n");
    exit(1);
}

//------------------------------------  R  ------------------------------------

void R(char* filename, int rp_pipe[]){
    printf("\n\x1b[33m[R] : Sono stato creato.\x1b[0m\n");

    int fd = open(filename, O_RDONLY);
    if(fd == -1) error("Impossibile aprire file.\n");

    struct stat file_stats;
    if(fstat(fd, &file_stats) == -1) error("Impossibile ottenre stats del file.\n");

    char* mapped_file = mmap(NULL, file_stats.st_size, PROT_READ, MAP_SHARED, fd, 0);
    if(mapped_file == MAP_FAILED) error("Impossibile mappare il file in memoria.\n");

    if(close(fd) == -1) error("Impossibile chiudere il file.\n");

    printf("\n\x1b[33m[R] : File mappato in memoria.\x1b[0m\n");

    close(rp_pipe[0]);

    if(write(rp_pipe[1], mapped_file, file_stats.st_size) < 0)
        error("R : Impossibile scrivere.\n");

    munmap(mapped_file, file_stats.st_size + sizeof(char));
    
    exit(0);
}

//-----------------------------------------------------------------------------

//------------------------------------  W  ------------------------------------

void W(int pw_pipe[]){
    printf("\n\x1b[34m[W] : Sono stato creato.\x1b[0m\n");

    close(pw_pipe[1]);
    char word[MAX_WORD_SIZE];
    while (1)
    {
        printf("merdaccia.\n");
        if(read(pw_pipe[0], word, MAX_WORD_SIZE) < 0)
            error("Impossibile leggere.\n");
        printf("merda.\n");
        printf("\n\x1b[34m[W] : %s.\x1b[0m\n", word);
        if(strcmp(word,"--end--") == 0) break;
    }
    
    exit(0);
}

//-------------------------------------  P  -----------------------------------

void P(int rp_pipe[], int pw_pipe[]){

    close(rp_pipe[1]);
    close(pw_pipe[0]);

    FILE* pipe_file = fdopen(rp_pipe[0], "r");

    char word[MAX_WORD_SIZE];

    for (int i = 0; i < 10; i++)
    {
        fgets(word, MAX_WORD_SIZE, pipe_file);
        int pal = 1;

        for (int i = 0; i < strlen(word)-1; i++)
        {
            if(word[i] != word[strlen(word)-i-2]){
                pal = 0;
                break;
            }
        }
        
        word[strcspn(word, "\n")] = 0;

        if(pal){
            //printf("%s è palindromo.\n", word);
            write(pw_pipe[1], word, MAX_WORD_SIZE);
        }
        
    }
    
    
    /*while (fgets(word, MAX_WORD_SIZE, pipe_file))
    {

        int pal = 1;

        for (int i = 0; i < strlen(word)-1; i++)
        {
            if(word[i] != word[strlen(word)-i-2]){
                pal = 0;
                break;
            }
        }
        
        word[strcspn(word, "\n")] = 0;

        if(pal){
            //printf("%s è palindromo.\n", word);
            write(pw_pipe[1], word, MAX_WORD_SIZE);
        }
        
    }       */

    printf("end\n");
    strcpy(word,"--end--");
    write(pw_pipe[1], word, MAX_WORD_SIZE);
    fclose(pipe_file);
}

//-----------------------------------------------------------------------------

//-----------------------------------  MAIN  ----------------------------------

int main(int argc, char const *argv[])
{   
    char filename[30] = "words.txt";
    
    //------------------ DICHIARAZIONE IPC ----------------

    int rp_pipe[2];
    if(pipe(rp_pipe) == -1) error("Impossibile creare rp_pipe\n");

    int pw_pipe[2];
    if(pipe(pw_pipe) == -1) error("Impossibile creare pw_pipe\n");

    //-----------------------------------------------------

    //-------------------  CREAZIONE FIGLI  ---------------

    int pid_r = fork();
    if(pid_r == 0) R(filename, rp_pipe);

    int pid_w = fork();
    if(pid_w == 0) W(pw_pipe);

    P(rp_pipe, pw_pipe);

    for (int i = 0; i < 2; i++)
    {
        wait(NULL);
    }
    

    return 0;
}

//-----------------------------------------------------------------------------