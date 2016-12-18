//take from the echoclient.c source 

#include "csapp.h"

int main(int argc, char **argv) 
{
    unsigned int clientfd, type, port, secretKey, errorNetwork;
    char *host, *fileNames;
    fileNames = calloc(40, 80);
    int error;
    rio_t rio;

    if (argc != 4) {
	fprintf(stderr, "usage: %s <host> <port> <key>\n", argv[0]);
	exit(0);
    }
    host = argv[1];
    port = atoi(argv[2]);
    secretKey = atoi(argv[3]);
    type = 3; 
	
    unsigned int networkOrderType = htonl(type);
    unsigned int networkSecretKey = htonl(secretKey);
     
    clientfd = Open_clientfd(host, port);
    Rio_readinitb(&rio, clientfd);
  
    Rio_writen(clientfd, &networkSecretKey, 4); 
    Rio_writen(clientfd, &networkOrderType, 4);
   
    Rio_readnb(&rio, &errorNetwork, 4);
    error = ntohl(errorNetwork);

    if ( error != 0 ) {
        printf("Error\n");
        return -1;
    }

    //we then receive the buffer with max 40 file names of length 80 each
    Rio_readnb(&rio, fileNames, 40*80);


    //Write all the files out here
    int isEndFound = 0;
    int offset = 0;
    while (!isEndFound) {
	if (*(fileNames+offset) != '\0') {
		printf("%s\n", fileNames+offset);
		offset +=80;
	} else {
		isEndFound = 1;
	}
    }
	
    free(fileNames);
    Close(clientfd); //line:netp:echoclient:close
    exit(0);
}
