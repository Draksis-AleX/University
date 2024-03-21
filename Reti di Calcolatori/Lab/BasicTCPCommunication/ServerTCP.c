#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFFLEN 512

void error(char *msg){
    printf("\n<! Error !>\n\t");
    perror(msg);
    exit(1);
}

int main(int argc, char const *argv[])
{
    int socket_fd, new_socket, n;
    struct sockaddr_in local_addr, remote_addr;
    socklen_t len = sizeof(struct sockaddr);
    char send_buffer[BUFFLEN];
    char recv_buffer[BUFFLEN];

    if(argc != 2) error("Inserisci due parametri.");

    if((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) error("Errore apertura socket");

    memset(&local_addr, 0, len);
    local_addr.sin_family = AF_INET;
    local_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    local_addr.sin_port = htons(atoi(argv[1]));

    if(bind(socket_fd, (struct sockaddr*) &local_addr, len) < 0) error("Errore nella bind");

    listen(socket_fd, 5);

    while (1)
    {
        new_socket = accept(socket_fd, (struct sockaddr*)&remote_addr, &len);

        if (fork() == 0)
        {
            close(socket_fd);
            while (1)
            {
                n = recv(new_socket, recv_buffer, BUFFLEN - 1, 0);
                recv_buffer[n] = 0;
                printf("\n[IP: %s - PORT: %d] : %s", inet_ntoa(remote_addr.sin_addr), ntohs(remote_addr.sin_port), recv_buffer);
            }
            close(new_socket);
            return 0;
        }
        else{
            close(new_socket);
        }
        
    }
    

    return 0;
}
