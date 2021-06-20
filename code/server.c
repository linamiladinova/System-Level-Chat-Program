#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> // 
#include <unistd.h>
#include <sys/socket.h> // for struct sockaddr
#include <netinet/in.h> // for INADDR_ANY
#include <sys/time.h>
#include <netdb.h> // for struct hostent


void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        fprintf(stderr, "ERROR, no port provided\n");
        exit(1);
    }
    int socketfd, newsocketfd, portno;
    int n;
    char buffer[1024] = {0};
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t clilen;
    
    socketfd = socket(AF_INET, SOCK_STREAM, 0); // returns a socket descriptor
    if (socketfd < 0)
    {
        error("ERROR opening socket");
    }

    bzero((char *) &serv_addr, sizeof(serv_addr)); //clearing everyting char 
    portno = atoi(argv[1]);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if(bind(socketfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    {
        error("ERROR on binding");
    }

    listen(socketfd, 5); //max 5 klienta na server-a ednovremnno
    clilen = sizeof(cli_addr);

    newsocketfd = accept(socketfd, (struct sockaddr *) &cli_addr, &clilen);

    if (newsocketfd < 0)
    {
        error("ERROR acceppting socket");
    }
    while (1)
    {
        bzero(buffer, 1024);
        n = read(newsocketfd, buffer, 1024);
        if (n < 0)
        {
            error("ERROR on reading.");
        }
        printf("Client: %s\n", buffer);
        bzero(buffer, 1024);
        fgets(buffer, 1024, stdin);
        
        n = write(newsocketfd, buffer, strlen(buffer));
        if(n < 0)
        {
            error("ERROR on writing.");
        }

        int i = strncmp("Buy", buffer, 3);
        if(i == 0);
        {
            break;
        }
    }
    close(newsocketfd);
    close(socketfd);
    return 0;
}
