#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>

#define BUFFLEN 512

void error(char *msg){
    printf("\n<! Error !>\n\t");
    perror(msg);
    exit(1);
}

int main(int argc, char const *argv[])
{
    int socket_fd, n;
    struct sockaddr_in dest_addr;
    char recv_buffer[BUFFLEN];
    char send_buffer[BUFFLEN];

    if(argc != 3) error("Inserisci IP e PORT");

    if((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) error("Errore apertura socket");

    memset(&dest_addr, 0, sizeof(dest_addr));
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_addr.s_addr = inet_addr(argv[1]);
    dest_addr.sin_port = htons(atoi(argv[2]));

    if(connect(socket_fd, (struct sockaddr*) &dest_addr, sizeof(dest_addr)) < 0) error("Connect Error");

    while (1)
    {
        printf("Write MSG\n\t");
        gets(send_buffer);
        
        send(socket_fd, send_buffer, strlen(send_buffer) + 1, 0);

        n = recv(socket_fd, recv_buffer, BUFFLEN - 1, 0);
        recv_buffer[n] = 0;
        printf("\n[IP: %s - PORT: %d] : %s", inet_ntoa(dest_addr.sin_addr), ntohs(dest_addr.sin_port), recv_buffer);
    }
    

    return 0;
}
