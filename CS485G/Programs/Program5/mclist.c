//take from the echoclient.c source 

#include "csapp.h"

int main(int argc, char **argv) 
{
    unsigned int clientfd, port, secretKey, type;
    char *host, buf[MAXLINE];
    rio_t rio;
    char fileName[80];   
    bzero(buf, MAXLINE);

    if (argc != 4) {
	fprintf(stderr, "usage: %s <host> <port> <key>\n", argv[0]);
	exit(0);
    }
    host = argv[1];
    port = atoi(argv[2]);
    secretKey = atoi(argv[3]);
    type = 3; 
	
    unsigned int networkOrderType = htons(type);
    unsigned int networkSecretKey = htons(secretKey);
    
    printf("key: %u\n" , networkSecretKey);
    printf("type: %u\n" , networkOrderType);

    clientfd = Open_clientfd(host, port);
    Rio_readinitb(&rio, clientfd);
  
    rio_writen(clientfd, &networkSecretKey, 4); 
    rio_writen(clientfd, &networkOrderType, 4);

    //Write all the files out here

    Close(clientfd); //line:netp:echoclient:close
    exit(0);
}
