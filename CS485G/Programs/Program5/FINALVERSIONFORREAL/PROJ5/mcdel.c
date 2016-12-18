//take from the echoclient.c source 

#include "csapp.h"
#define MAXFILENAME 80
#define INTBYTES 4
int main(int argc, char **argv) 
{
    unsigned int clientfd, port, secretKey, type, networkError;
    char *host, buf[MAXLINE];
    rio_t rio;
    char fileName[MAXFILENAME];   
    bzero(buf, MAXLINE);
    int error;

    if (argc != 5) {
	fprintf(stderr, "usage: %s <host> <port> <key> <filename>\n", argv[0]);
	exit(0);
    }
    host = argv[1];
    port = atoi(argv[2]);
    secretKey = atoi(argv[3]);
    strncpy(fileName, argv[4], MAXFILENAME);
    type = 2; 
	
    unsigned int networkOrderType = htonl(type);
    unsigned int networkSecretKey = htonl(secretKey);
    
    clientfd = Open_clientfd(host, port);
    Rio_readinitb(&rio, clientfd);
  
    Rio_writen(clientfd, &networkSecretKey, INTBYTES); 
    Rio_writen(clientfd, &networkOrderType, INTBYTES);
    Rio_writen(clientfd, &fileName, MAXFILENAME);  

    Rio_readnb(&rio, &networkError, INTBYTES);
    error = ntohl(networkError);

    if ( error != 0 ) {
        printf("ERROR\n");
        return -1;
    }

    Close(clientfd); //line:netp:echoclient:close
    exit(0);
}
