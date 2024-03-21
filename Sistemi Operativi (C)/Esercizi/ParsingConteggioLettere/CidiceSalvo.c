#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
    int pid;
    int shm_id = shmget(IPC_PRIVATE, sizeof(char) * 1000, IPC_CREAT | IPC_EXCL | 0600);

    if(shm_id == -1){
        printf("[ERROR]: errore creazione zona condivisa \n\n");
    }


    pid = fork();

    if (pid != 0){
        //CORPO DEL PADRE 
        int *shm_mat;
        shm_mat = (int *)shmat(shm_id, NULL , 0);

        if(shm_mat == (int *)-1){
            printf("[ERROR]: errore associazione alla memoria condivisa \n\n");
        }

        FILE * file = fopen("text.txt","r");

        if (file==NULL){ printf("[ERROR]: errore apertura file \n\n"); perror("anello.txt"); }
        else{

            char line[1000];

            //printf("[FILE]:");
            while(fgets(line, sizeof(line) , file)){
                //printf("[FILE]: %s\n",line);
                int i=0;
                while(line[i]!='\0'){
                    shm_mat[i] = line[i];
                    //printf("%c",shm_mat[i]);
                    i++;
                }
            }
        }


        fclose(file);
        shmdt(shm_mat);

    }
    else if(pid==-1){  printf("[ERROR]: errore creazione processi figlio \n"); }
    else{
        //CORPO FIGLIO
         sleep(1000);
        char* shm = (char *)shmat(shm_id, NULL , SHM_RDONLY);

        int i=0;
        while(shm[i]!='\0'){
            printf("%c",shm[i]);
            i++;
        }

        shmdt(shm);

    }

    shmctl(shm_id,IPC_RMID, NULL);

}