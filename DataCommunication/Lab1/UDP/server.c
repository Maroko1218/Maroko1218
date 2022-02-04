#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char const *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <port>", argv[0]);
        exit(0);
    }

    int port = atoi(argv[1]);
    int sockfd;
    struct sockaddr_in si_me, si_other;
    char buffer [1024];
    socklen_t addr_size;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&si_me, '\0', sizeof(si_me));
    si_me.sin_family=AF_INET;
    si_me.sin_port=htons(port);
    si_me.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr*)&si_me, sizeof(si_me));
    printf("Socket bount to server address\n");
    addr_size = sizeof(si_other);
    recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr*)&si_other, &addr_size);
    printf("Data received: %s\n", buffer);
    
    //if data received = "time"
    //replace buffer with time
    //send time int from time.h (for example)
    
    sendto(sockfd, buffer, 1024, 0, (struct sockaddr*)&si_other, addr_size);
    printf("Data sent: %s\n", buffer);        
    return 0;
}
