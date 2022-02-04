#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char **argv){
    if (argc != 2){
        printf("Usage: %s <port>",argv[0]);
        exit(0);
    }

    int port = atoi(argv[1]);
    int sockfd;
    struct sockaddr_in serverAddr;
    char buffer [1024];
    socklen_t addr_size;

    sockfd = socket(PF_INET, SOCK_DGRAM, 0);

    memset(&serverAddr, '\0', sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    inet_pton(AF_INET, "83.249.224.202", &serverAddr.sin_addr);
    
    strcpy(buffer, "Hello Server\n");
    memset(buffer, '\0', sizeof(buffer));
    sendto(sockfd, buffer, 1024, 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    printf("Data sent: %s\n", buffer);
    
    addr_size = sizeof(serverAddr);
    recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr*)&serverAddr, &addr_size);
    for (int i = 0; i < 1024; i++)
    {
        printf("%c",buffer[i]);
    }
    
    return 0;
}