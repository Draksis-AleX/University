#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <sys/sem.h>
#include <ctype.h>

#define MAX_DESCR_LEN 100
#define MAX_LINE_LEN 1024
#define MAX_BIDDERS_NUM 16

void error(char* msg){
    printf("\n\x1b[31m<< Errore >>\n\t");
    perror(msg);
    printf("\x1b[0m\n");
    exit(1);
}

void WAIT(sem, n){
    struct sembuf op[1] = {{n, -1, 0}};
    semop(sem, op, 1);
}

void SIGNAL(sem, n){
    struct sembuf op[1] = {{n, +1, 0}};
    semop(sem, op, 1);
}

typedef struct{
    char description[MAX_DESCR_LEN];
    int bidders_done[MAX_BIDDERS_NUM];
    int min_offer;
    int max_offer;
    int offer;
    int id_bidder;
    int end;
} auction_msg;

typedef struct{
    int id_bidder;
    int amount;
} winner;

//----------------------------------  JUDGE  ----------------------------------

void J(int shm_id, int sem_j, int sem_b, char* filename, int n_bidders){

    auction_msg* shared_space = (auction_msg*) shmat(shm_id, NULL, 0);
    if(shared_space == (auction_msg*) -1) error("\n[[JUDGE]] : Impossibile associare zona di memoria condivisa.\n");

    FILE* auction_file = fopen(filename, "r");

    char line[MAX_LINE_LEN];

    shared_space->end = 0;
    while (fgets(line, MAX_LINE_LEN, auction_file))
    {   
        char descr[MAX_DESCR_LEN];
        strcpy(descr, strtok(line, ","));

        int min_offer = atoi(strtok(NULL, ","));
        int max_offer = atoi(strtok(NULL, ","));

        printf("\n[[JUDGE]] : Auction\n\tDescription : %s\n\tMinimum Offer : %d\n\tMaxinum Offer : %d\n", descr, min_offer, max_offer);

        strcpy(shared_space->description, descr);
        shared_space->max_offer = max_offer;
        shared_space->min_offer = min_offer;
        shared_space->offer = 0;
        shared_space->id_bidder = 0;
        for (int i = 0; i < n_bidders; i++)
        {
            shared_space->bidders_done[i] = 0;
        }
        

        winner winning_b;
        int valid_offers = 0;
        winning_b.id_bidder = -1;
        winning_b.amount = -1;
        for (int i = 0; i < n_bidders; i++)
        {
            SIGNAL(sem_b, 0);
            WAIT(sem_j, 0);
            printf("\n[JUDGE] Offerta ricevuta dal bidder %d: %d\n",shared_space->id_bidder, shared_space->offer);
            if(shared_space->offer >= shared_space->min_offer){
                if(shared_space->offer > winning_b.amount){
                    winning_b.amount = shared_space->offer;
                    winning_b.id_bidder = shared_space->id_bidder;
                }
                valid_offers++;
            }
            else printf("\n[JUDGE] : Offerta del bidder %d NON valida.\n", shared_space->id_bidder);
        }

        printf("\n\n[JUDGE] : L'asta per %s si conclude con %d offerte valide.\nIl vincitore dell'asta è il bidder %d con un offerta di %d.\n\n",shared_space->description, valid_offers, winning_b.id_bidder, winning_b.amount);

    }

    shared_space->end = 1;
    for (int i = 0; i < n_bidders; i++)
    {
        SIGNAL(sem_b,0);
    }
    
    
    fclose(auction_file);
}

//-----------------------------------------------------------------------------

//---------------------------------  BIDDER  ----------------------------------

void B(int shm_id, int sem_j, int sem_b, int id_bidder){
    printf("\n[[BIDDER %d]] : Sono stato creato.\n", id_bidder);

    auction_msg* shared_space = (auction_msg*) shmat(shm_id, NULL, 0);
    if(shared_space == (auction_msg*) -1) error("\n[[BIDDER]] : Impossibile associare zona di memoria condivisa.\n");
    srand(getpid() * time(NULL));
    while(1){
        WAIT(sem_b, 0);
        
        if(shared_space->end == 1) break;

        if(shared_space->bidders_done[id_bidder-1] == 1){
            SIGNAL(sem_b, 0);
            continue;
        }
        
        int myoffer = rand()%shared_space->max_offer;
        //printf("\n[BIDDER %d] : Sto facendo un offerta di %d.\n", id_bidder, myoffer);
        shared_space->bidders_done[id_bidder-1] = 1;
        shared_space->id_bidder = id_bidder;
        shared_space->offer = myoffer;
        SIGNAL(sem_j, 0);
    }

    exit(0);
}

//-----------------------------------------------------------------------------

//-----------------------------------  MAIN  ----------------------------------

int main(int argc, char const *argv[])
{
    /*if(argc < 3) error("Numero di argomenti insufficienti.\n");
    int n_bidders = argv[2];
    char* filename = argv[1];*/
    int n_bidders = 4;
    char filename[30];
    strcpy(filename, "auctions.txt");

    //----------------  DICHIARAZIONE IPC  ----------------

    int shm_id = shmget(IPC_PRIVATE, sizeof(auction_msg), IPC_CREAT | 0600);
    if(shm_id == -1) error("Impossibile creare zona di memoria condivisa.\n");

    int sem_j = semget(IPC_PRIVATE, 1, IPC_CREAT | 0600);
    if(sem_j == -1) error("Impossibile creare sem_j.\n");
    if(semctl(sem_j, 0, SETVAL, 0) == -1) error("Impossibile settare a 0 sem_j.\n");

    int sem_b = semget(IPC_PRIVATE, 1, IPC_CREAT | 0600);
    if(sem_b == -1) error("Impossibile creare sem_b.\n");
    if(semctl(sem_b, 0, SETVAL, 0) == -1) error("Impossibile settare a 0 sem_b.\n");

    //-----------------------------------------------------

    //---------------- CREAZIONE FIGLI  -------------------

    for (int i = 0; i < n_bidders; i++)
    {
        int pid_bidder = fork();
        if(pid_bidder == 0) B(shm_id, sem_j, sem_b, i+1);
    }

    J(shm_id, sem_j, sem_b, filename, n_bidders);

    for (int i = 0; i < n_bidders; i++)
    {
        wait(NULL);
    }

    //-----------------------------------------------------

    //----------------- DISTRUZIONE IPC  ------------------

    if(shmctl(shm_id, IPC_RMID, NULL) < 0) error("Impossibile distruggere zona di memoria condivisa.\n");
    if(semctl(sem_j, 0, IPC_RMID, NULL) < 0) error("Impossibile distruggere sem_j.\n");
    if(semctl(sem_b, 0, IPC_RMID, NULL) < 0) error("Impossibile distruggere sem_b.\n");
    
    return 0;
}
