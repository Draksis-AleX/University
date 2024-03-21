#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <time.h>

typedef struct{
    long type;
    short player_id;
    short n;
} pd_msg;

void error(char* msg){
    printf("\x1b[31m\n\n<< Errore >>\n\t");
    perror(msg);
    printf("\x1b[0m\n");
    exit(1);
}

//---------------------------------  P  ---------------------------------------

void P(int msg_id, int id){

    srand(getpid() * time(NULL));
    pd_msg msg;
    while (1)
    {   
        if(msgrcv(msg_id, &msg, sizeof(pd_msg) - sizeof(long), id+1, 0) < 0)
            error("[P] : Impossibile ricevere messaggio.\n");
        if(msg.n == -1){
            msg.type = 7;
            msg.n = rand()%10;
            msg.player_id = id;
            msgsnd(msg_id, &msg, sizeof(pd_msg) - sizeof(long), 0);
        }
        else if(msg.n == -2) break; 
    }
    
    exit(0);
}

//-----------------------------------------------------------------------------

//---------------------------------  J  ---------------------------------------

void J(int msg_id, int n_player, int n_games){

    int i = 0;
    pd_msg msg;
    int won_games[n_player];
    for (int i = 0; i < n_player; i++) won_games[i] = 0;
    
    while(i < n_games){
        printf("\x1b[30m\n\n--  [[  GAME  %d  ]]  --\x1b[0m\n\n", i+1);
        msg.n = -1;
        for (int i = 0; i < n_player; i++)
        {
            msg.type = i + 1;
            if(msgsnd(msg_id, &msg, sizeof(pd_msg) - sizeof(long), 0) < 0)
                error("[J] : Impossibile inviare messaggio.\n");
        }
        
        int p_n[n_player];
        int replay = 0;
        for (int i = 0; i < n_player; i++)
        {
            msgrcv(msg_id, &msg, sizeof(pd_msg) - sizeof(long), 7, 0);
            printf("\n[J] : Il giocatore %d ha scelto %d.\n", msg.player_id, msg.n);
            p_n[msg.player_id] = msg.n;
            for (int j = 0; j < i; j++)
            {
                if(p_n[j] == p_n[i]){
                    replay = 1;
                }
            }
        }

        if(replay == 0){
            int winner_id = 0;
            for (int i = 0; i < n_player; i++)
            {
                winner_id += p_n[i];
            }

            winner_id = winner_id%n_player;
            won_games[winner_id]++;
            printf("\x1b[32m\n\nThe WINNER is Player %d\x1b[0m\n\n", winner_id);
            
            i++;
        }
        else printf("\x1b[33m\n\nIl Game va rigiocato.\x1b[0m\n\n");

        printf("\x1b[30m\n--------------------------------------------\x1b[0m\n");

    }

    msg.n = -2;
    for (int i = 0; i < n_player; i++)
    {   
        msg.type = i+1;
        if(msgsnd(msg_id, &msg, sizeof(pd_msg) - sizeof(long), 0) < 0)
            error("[J] : Impossibile inviare messaggio.\n");
    }
    
    

    printf("\x1b[34m\n\n-------------  Classifica  ---------------\x1b[0m\n\n");
    int winner_id = 0;
    for (int i = 0; i < n_player; i++)
    {
        printf("\x1b[34m\nPlayer %d : %d Game vinti.\x1b[0m\n",i,won_games[i]);
        if(won_games[winner_id] < won_games[i]) winner_id = i;
    }
    printf("\x1b[34m\n\n[[  Il vincitore assoluto è il player %d !  ]]\x1b[0m\n\n",winner_id);
    

}

//-----------------------------------------------------------------------------

//--------------------------------  MAIN  -------------------------------------

int main(int argc, char const *argv[])
{

    /*if(argc < 3) error("Numero di parametri insufficiente.\n");
    int n_player = argv[1];
    int n_games = argv[2];*/

    int n_player = 6;
    int n_games = 5;

    //-----------------  DICHIARAZIONE IPC  ---------------

    int msg_id = msgget(IPC_PRIVATE, IPC_CREAT | IPC_EXCL | 0660);
    if(msg_id == -1) error("Impossibile creare coda di messaggi.\n");

    //-----------------------------------------------------

    //----------------  CREAZIONE FIGLI  ------------------

    for (int i = 0; i < n_player; i++)
    {
        int pid = fork();
        if(pid == 0) P(msg_id, i);
    }
    
    J(msg_id, n_player, n_games);
    
    for (int i = 0; i < n_player; i++) wait(NULL);

    //-----------------------------------------------------

    //-----------------  DISTRUZIONE IPC  -----------------

    if(msgctl(msg_id, IPC_RMID, NULL) == -1) error("Impossibile distruggere coda di messaggi.\n");

    return 0;
}

//-----------------------------------------------------------------------------
