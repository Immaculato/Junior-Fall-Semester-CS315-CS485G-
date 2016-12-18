//take from the echoclient.c source 

#include "csapp.h"
#define MAXFILESIZE 100 * 1024

int main(int argc, char **argv) 
{
    unsigned int clientfd, type, port, secretKey, errorNetwork;
    char *host, buf[MAXLINE], fileBuf[MAXFILESIZE];
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
    type = 1; 
	
    unsigned int networkOrderType = htonl(type);
    unsigned int networkSecretKey = htonl(secretKey);
    
    clientfd = Open_clientfd(host, port);
    Rio_readinitb(&rio, clientfd);
  
    Rio_writen(clientfd, &networkSecretKey, 4); 
    Rio_writen(clientfd, &networkOrderType, 4);
    Rio_writen(clientfd, &fileName, 80);  
/*
    while (Fgets(buf, MAXLINE, stdin) != NULL) {
	Rio_writen(clientfd, buf, strlen(buf));
	Rio_readlineb(&rio, buf, MAXLINE);
	Fputs(buf, stdout);
    }
*/

    unsigned int numBytes = fread(fileBuf, sizeof(unsigned char), MAXFILESIZE, stdin);
    printf("read byte amnt: %i\n", numBytes);
    unsigned int numNetOrderBytes = htonl(numBytes);
    rio_writen(clientfd, &numNetOrderBytes, 4);
    //we must write it in chunks because only ~ 10000 bytes can be written at a time.
    int areBytesRemaining = 1;
    int offset = 0;
    while (areBytesRemaining) {
        if (numBytes>10000) Rio_writen(clientfd, fileBuf+offset, 10000);
	else { 
		Rio_writen(clientfd, fileBuf+offset, numBytes);
		areBytesRemaining = 0;
	}
	offset+=10000;
	numBytes-=10000;
    }

    //get the error code from the server and process it accordingly.
    Rio_readn(clientfd, &errorNetwork, 4);
    error = ntohl(errorNetwork);

    if ( error != 0 ) {
        printf("Error\n");
        return -1;
    }
    
    Close(clientfd); //line:netp:echoclient:close
    exit(0);
}
