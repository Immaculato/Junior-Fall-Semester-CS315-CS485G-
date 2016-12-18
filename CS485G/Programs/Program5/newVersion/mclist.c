//take from the echoclient.c source 

#include "csapp.h"

int main(int argc, char **argv) 
{
    unsigned int clientfd, port, secretKey, type;
    char *host, *fileNames;
    fileNames = calloc(40, 80);
    rio_t rio;

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
