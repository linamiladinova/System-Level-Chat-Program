/*
filename server_ipaddress portno
argv[0] - filename
argv[1] - server ip
argv[3] - port number
*/

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> // 
#include <sys/socket.h> // for struct sockaddr
#include <netinet/in.h> // for INADDR_ANY
#include <sys/time.h>
#include <netdb.h> // for struct hostent

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    if(argc < 3)
    {
        fprintf(stderr, "usage, %s hosname port.\n", argv[0]);
        exit(1);
    }

    int socketfd, portno;
    int n;
    char buffer[1024] = {0};
    struct sockaddr_in serv_addr;
    struct hostent *server;
    
    portno = atoi(argv[2]);
    socketfd = socket(AF_INET, SOCK_STREAM, 0); // returns a socket descriptor
    if (socketfd < 0)
    {
        error("ERROR opening socket");
    }

    server = gethostbyname(argv[1]);
    if (server == NULL)
    {
        fprintf(stderr, "ERROR - no hostname.");
    }
    bzero((char *) &sevr_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr->h_lenght);
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (connect(socketfd, (structur sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    {
        error("ERROR in the connection.");
    }
    while (1)
    {
        bzero(buffer, 1024);
        fgetc(buffer, 1024);
        n = write(socketfd, buffer, 1024);
        if (n < 0)
        {
            error("ERROR on writing.");
        }
        bzero(buffer, 1024);
        
        n = read(socketfd, buffer, 1024);
        if (n < 0)
        {
            error("ERROR on reading.");
        }
        printf("Server: %s". buffer);
        int i = strcmp("Buy", buffer, 3) //3 zashtoto e 3ti argument vyv funciqta write
        if(i == 0)
        {
            break;
        }
    }

    close(socketfd);
    return 0;
}
