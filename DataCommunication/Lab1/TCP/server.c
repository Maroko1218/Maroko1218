#include <sys/types.h> /* This is the server code */
#include <sys/fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define SERVER_PORT 8080 /* arbitrary, but client & server must agree */
#define BUF_SIZE 4096     /* block transfer size */
#define QUEUE_SIZE 10
#define WEBPAGE_FOLDER "sample_website/"

void fatal(char *string) {
    printf("%s\n", string);
    exit(1);
}

void sendresponse(int response, int sa, char *buf) {
    switch (response)
    {
    case 200:
        if (strstr(buf, "index")) {
            write(sa, "HTTP/1.0 200 OK\r\nServer: Demo Web Server\r\nContent-Length: 873\r\nContent-Type: text/html\r\n\r\n", 90);
        } else if (strstr(buf, "quokka")) {
            write(sa, "HTTP/1.0 200 OK\r\nServer: Demo Web Server\r\nContent-Length: 316243\r\nContent-Type: image/jpeg\r\n\r\n", 94);
        }
        break;
    case 404:
        write(sa, "HTTP/1.0 404 Not Found\r\n\r\n", 27);
        break;
    default:
        break;
    }
}

char* parserequest(char* buf) {
    char *temp = (char*)malloc(sizeof(char) * BUF_SIZE);
    if (strstr(buf, "GET ")) {
        int i = 0;
        for (i = 0; i < strlen(WEBPAGE_FOLDER); i++) {
            temp[i] = WEBPAGE_FOLDER[i];
        }
        
        while(buf[i+5-strlen(WEBPAGE_FOLDER)] != ' ') {
            temp[i] = buf[i+5-strlen(WEBPAGE_FOLDER)];
            i++;
        }
        temp[i+1] = '\0';
    }
    return temp;
}

int main(int argc, char *argv[]) {
    int s, b, l, fd, sa, bytes, on = 1;
    char buf[BUF_SIZE];         /* buffer for outgoing file */
    struct sockaddr_in channel; /* holds IP address */
    /*
     * Build address structure to bind to socket. */
    memset(&channel, 0, sizeof(channel)); /* zero channel */
    channel.sin_family = AF_INET;
    channel.sin_addr.s_addr = htonl(INADDR_ANY);
    channel.sin_port = htons(SERVER_PORT);
    /*
     * Passive open. Wait for connection. */
    s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); /* create socket */
    if (s < 0) {
        fatal("socket failed");
    }
    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on));
    b = bind(s, (struct sockaddr *)&channel, sizeof(channel));
    if (b < 0){
        fatal("bind failed");
    }
    l = listen(s, QUEUE_SIZE); /* specify queue size */
    if (l < 0) {
        fatal("listen failed");
    }
    /*
     * Socket is now set up and bound. Wait for connection and process it. */
    while (1) {
        sa = accept(s, 0, 0); /* block for connection request */
        if (sa < 0) {
            fatal("accept failed");
        }
        read(sa, buf, BUF_SIZE); /* read file name from socket */
        /*
         * Get and return the file. */
        printf("%s\n", parserequest(buf));
        fd = open(parserequest(buf), O_RDONLY); /* open the file to be sent back */
        if (fd < 0) {
            sendresponse(404, sa, buf);
        } else {
            sendresponse(200, sa, parserequest(buf));
            while (1) {
                bytes = read(fd, buf, BUF_SIZE); /* read from file */
                if (bytes <= 0) {
                    break;             /* check for end of file */
                }
                write(sa, buf, bytes); /* write bytes to socket */
            }
        }
        close(fd); /* close file */
        close(sa); /* close connection */
    }
}