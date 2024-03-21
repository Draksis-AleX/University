#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define MAX_KEY_LEN 64
#define MAX_LINE_LEN 128

typedef struct
{
    int proc_id;
    char key[MAX_KEY_LEN];
}query_msg;

typedef struct{
    char key[MAX_KEY_LEN];
    int value;
}entry;

typedef struct
{
    int proc_id;
    char key[MAX_KEY_LEN];
    int value;
}db_msg;


void error(char* msg){
    printf("\n\n\x1b[31m<< Errore >>\n\t");
    perror(msg);
    printf("\x1b[0m\n");
}

void WAIT(int sem){
    struct sembuf op[1] = {{0,-1,0}};
    semop(sem, op, 1);
}

void SIGNAL(int sem){
    struct sembuf op[1] = {{0,+1,0}};
    semop(sem, op, 1);
}

//-----------------------------------  DB  ------------------------------------

void DB(int n_queries, char* filename, int shm_indb_id, int sem_w_indb, int sem_r_indb, int shm_dbout_id, int sem_w_dbout, int sem_r_dbout){
    printf("\x1b[32m[DB] : Sono stato creato.\x1b[0m\n");

    FILE* db_file = fopen(filename, "r");
    if(db_file == NULL) error("[DB] : Impossibile aprire file.\n");

    int n_entries = 0;
    char line[MAX_LINE_LEN];
    while (fgets(line, MAX_LINE_LEN, db_file)) n_entries++;
    
    rewind(db_file);

    entry* entries = malloc(sizeof(entry) * n_entries);
    int i = 0;
    while (fgets(line, MAX_LINE_LEN, db_file))
    {
        char* key = strtok(line,":");
        int value = atoi(strtok(NULL,"\n"));
        strcpy(entries[i].key, key);
        entries[i].value = value;
        i++;
    }

    query_msg* shm_indb = (query_msg*) shmat(shm_indb_id, NULL, 0);
    if(shm_indb == (query_msg*) -1) error("[DB] : Impossibile associare zona di memoria shm_indb.\n");

    db_msg* shm_dbout = (db_msg*) shmat(shm_dbout_id, NULL, 0);
    if(shm_dbout == (db_msg*) -1) error("[DB] : Impossibile associare zona di memoria shm_dbout.\n");

    SIGNAL(sem_w_indb);

    int dead_counter = 0;

    while (1)
    {
        WAIT(sem_r_indb);

        if(shm_indb->proc_id == -1) dead_counter++;
        if(dead_counter >= n_queries) break;

        //printf("\x1b[32m[DB] : Query ricevuta da IN-%d -> %s\x1b[0m\n", shm_indb->proc_id, shm_indb->key);

        int val = -1;
        for (int i = 0; i < n_entries; i++)
        {
            //printf("\nIs %s == %s ?", shm_indb->key, entries[i]);
            if(strcmp(shm_indb->key, entries[i].key) == 0){
                val = entries[i].value;
                break;
            }
        }
        
        if(val != -1){
            printf("\x1b[32m[DB] : Key %s trovata -> Value = %d\x1b[0m\n",shm_indb->key, val);

            WAIT(sem_w_dbout);

            shm_dbout->proc_id = shm_indb->proc_id;
            strcpy(shm_dbout->key, shm_indb->key);
            shm_dbout->value = val;

            SIGNAL(sem_r_dbout);

        }
        else{
            printf("\x1b[32m[DB] : Key %s NON presente nel database.\x1b[0m\n", shm_indb->key);
        }

        SIGNAL(sem_w_indb);
    }

    WAIT(sem_w_dbout);

    shm_dbout->proc_id = -1;

    SIGNAL(sem_r_dbout);
    
    shmdt(shm_indb);
    shmdt(shm_dbout);
    fclose(db_file);
    exit(0);
}

//-----------------------------------------------------------------------------

//---------------------------------  OUT  -------------------------------------

void OUT(int n_queries, int shm_dbout_id, int sem_w_dbout, int sem_r_dbout){
    printf("\x1b[33m[OUT] : Sono stato creato.\x1b[0m\n");

    db_msg* shm_dbout = (db_msg*) shmat(shm_dbout_id, NULL, 0);
    if(shm_dbout == (db_msg*) -1) error("[DB] : Impossibile associare zona di memoria shm_dbout.\n");

    int proc_values[n_queries];
    int valid_queries[n_queries];

    for (int i = 0; i < n_queries; i++){
        proc_values[i] = 0;
        valid_queries[i] = 0;
    }

    SIGNAL(sem_w_dbout);

    while (1)
    {
        WAIT(sem_r_dbout);

        if(shm_dbout->proc_id == -1) break;

        //printf("\x1b[33m[OUT] : Ricevuto messaggio da DB\n\tproc_id = %d\n\tkey = %s\n\tvalue = %d\x1b[0m\n", shm_dbout->proc_id, shm_dbout->key, shm_dbout->value);
        proc_values[shm_dbout->proc_id] += shm_dbout->value;
        valid_queries[shm_dbout->proc_id]++;

        SIGNAL(sem_w_dbout);

    }

    for (int i = 0; i < n_queries; i++)
    {
        printf("\x1b[33m[OUT] : Ricevute %d key valide da IN-%d\nValore complessivo = %d.\x1b[0m\n", valid_queries[i], i, proc_values[i]);
    }
    
    
    shmdt(shm_dbout);
    exit(0);
}

//-----------------------------------------------------------------------------

//----------------------------------  IN  -------------------------------------

void IN(int id, char* query_filename, int shm_indb_id, int sem_w_indb, int sem_r_indb){
    printf("\x1b[34m[IN-%d] : Sono stato creato.\x1b[0m\n",id);

    FILE* query_file = fopen(query_filename, "r");
    if(query_file == NULL) error("[IN] : Impossibile aprire il file.\n");

    query_msg* shm_indb = (query_msg*) shmat(shm_indb_id, NULL, 0);
    if(shm_indb == (query_msg*) -1) error("[IN] : Impossibile associare zona di memoria shm_indb.\n");

    char key[MAX_KEY_LEN];
    while (fgets(key, MAX_KEY_LEN, query_file))
    {
        //printf("\x1b[34m[IN-%d] : [%s].\x1b[0m\n",id,key);

        WAIT(sem_w_indb);

        key[strcspn(key,"\n")] = 0;
        strcpy(shm_indb->key, key);
        shm_indb->proc_id = id;

        printf("\x1b[34m[IN-%d] : Inviata query [%s].\x1b[0m\n",id,key);

        SIGNAL(sem_r_indb);
    }

    WAIT(sem_w_indb);

    shm_indb->proc_id = -1;

    SIGNAL(sem_r_indb);
    
    shmdt(shm_indb);
    fclose(query_file);
    exit(0);
}

//-----------------------------------------------------------------------------

//----------------------------------  MAIN  -----------------------------------

int main(int argc, char const *argv[])
{
    
    char filename[30];
    strcpy(filename, "database.txt");
    int n_queries = 2;
    char query_file[n_queries][30];
    strcpy(query_file[0], "query1.txt");
    strcpy(query_file[1], "query2.txt");

    //----------------  DICHIARAZIONE IPC  ----------------

    int shm_indb_id = shmget(IPC_PRIVATE, sizeof(query_msg), IPC_CREAT | 0600);
    if(shm_indb_id == -1) error("Impossibile creare zona di memoria shm_indb_id.\n");

    int shm_dbout_id = shmget(IPC_PRIVATE, sizeof(db_msg), IPC_CREAT | 0600);
    if(shm_dbout_id == -1) error("Impossibile creare zona di memoria shm_dbout_id.\n");

    int sem_w_indb = semget(IPC_PRIVATE, 1, IPC_CREAT | 0600);
    if(sem_w_indb == -1) error("Impossibile creare sem_w_indb.\n");
    if(semctl(sem_w_indb, 0, SETVAL, 0) == -1) error("Impossibile impostare sem_w_indb a 0.\n");

    int sem_r_indb = semget(IPC_PRIVATE, 1, IPC_CREAT | 0600);
    if(sem_r_indb == -1) error("Impossibile creare sem_w_indb.\n");
    if(semctl(sem_r_indb, 0, SETVAL, 0) == -1) error("Impossibile impostare sem_r_indb a 0.\n");

    int sem_w_dbout = semget(IPC_PRIVATE, 1, IPC_CREAT | 0600);
    if(sem_w_dbout == -1) error("Impossibile creare sem_w_indb.\n");
    if(semctl(sem_w_dbout, 0, SETVAL, 0) == -1) error("Impossibile impostare sem_w_dbout a 0.\n");

    int sem_r_dbout = semget(IPC_PRIVATE, 1, IPC_CREAT | 0600);
    if(sem_r_dbout == -1) error("Impossibile creare sem_w_indb.\n");
    if(semctl(sem_r_dbout, 0, SETVAL, 0) == -1) error("Impossibile impostare sem_r_dbout a 0.\n");

    //-----------------------------------------------------

    //--------------  CREAZIONE FIGLI  --------------------

    int pid_db = fork();
    if(pid_db == 0) DB(n_queries, filename, shm_indb_id, sem_w_indb, sem_r_indb, shm_dbout_id, sem_w_dbout, sem_r_dbout);

    int pid_out = fork();
    if(pid_out == 0) OUT(n_queries, shm_dbout_id, sem_w_dbout, sem_r_dbout);

    for (int i = 0; i < n_queries; i++)
    {
        int pid_in = fork();
        if(pid_in == 0) IN(i, query_file[i], shm_indb_id, sem_w_indb, sem_r_indb);
    }

    for (int i = 0; i < n_queries + 2; i++)
    {
        wait(NULL);
    }

    //-----------------------------------------------------
    
    //-------------- DISTRUZIONE IPC  ---------------------

    if(shmctl(shm_indb_id, IPC_RMID, NULL) == -1) error("Impossibile cancellare zona di memoria shm_indb_id.\n");
    if(shmctl(shm_dbout_id, IPC_RMID, NULL) == -1) error("Impossibile cancellare zona di memoria shm_dbout_id.\n");
    if(semctl(sem_r_indb, 0, IPC_RMID, NULL) < 0) error("Impossibile cancellare sem_r_indb.\n");
    if(semctl(sem_w_indb, 0, IPC_RMID, NULL) < 0) error("Impossibile cancellare sem_w_indb.\n");
    if(semctl(sem_r_dbout, 0, IPC_RMID, NULL) < 0) error("Impossibile cancellare sem_r_dbout.\n");
    if(semctl(sem_w_dbout, 0, IPC_RMID, NULL) < 0) error("Impossibile cancellare sem_w_dbout.\n");

    return 0;
}

