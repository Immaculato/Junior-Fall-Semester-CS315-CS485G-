//take from the echoclient.c source 

#include "csapp.h"

int main(int argc, char **argv) 
{
    unsigned int clientfd, port, secretKey, type, networkError;
    char *host, buf[MAXLINE];
    rio_t rio;
    char fileName[80];   
    bzero(buf, MAXLINE);
    int error;

    if (argc != 5) {
	fprintf(stderr, "usage: %s <host> <port> <key> <filename>\n", argv[0]);
	exit(0);
    }
    host = argv[1];
    port = atoi(argv[2]);
    secretKey = atoi(argv[3]);
    strncpy(fileName, argv[4], 80);
    type = 2; 
	
    unsigned int networkOrderType = htonl(type);
    unsigned int networkSecretKey = htonl(secretKey);
    
    clientfd = Open_clientfd(host, port);
    Rio_readinitb(&rio, clientfd);
  
    Rio_writen(clientfd, &networkSecretKey, 4); 
    Rio_writen(clientfd, &networkOrderType, 4);
    Rio_writen(clientfd, &fileName, 80);  

    Rio_readnb(&rio, &networkError, 4);
    error = ntohl(networkError);

    if ( error != 0 ) {
        printf("ERROR\n");
        return -1;
    }

    Close(clientfd); //line:netp:echoclient:close
    exit(0);
}
