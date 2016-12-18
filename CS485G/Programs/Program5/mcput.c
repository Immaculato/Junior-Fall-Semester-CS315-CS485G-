//take from the echoclient.c source 

#include "csapp.h"

const int MAXFILESIZE = 100*1024;

int main(int argc, char **argv) 
{
    unsigned int clientfd, port, secretKey, type;
    char *host, fileBuf[MAXFILESIZE];
    rio_t rio;
    char fileName[80];   
    bzero(fileBuf, MAXLINE);

    if (argc != 5) {
	fprintf(stderr, "usage: %s <host> <port> <key> <filename>\n", argv[0]);
	exit(0);
    }
    host = argv[1];
    port = atoi(argv[2]);
    secretKey = atoi(argv[3]);
    strncpy(fileName, argv[4], 80);
    type = 1; 
	
    unsigned int networkOrderType = htons(type);
    unsigned int networkSecretKey = htons(secretKey);
    
    printf("key: %u\n" , networkSecretKey);
    printf("type: %u\n" , networkOrderType);
    printf("filname: %s\n" , fileName);    

    clientfd = Open_clientfd(host, port);
    Rio_readinitb(&rio, clientfd);
  
    rio_writen(clientfd, &networkSecretKey, 4); 
    rio_writen(clientfd, &networkOrderType, 4);
    rio_writen(clientfd, &fileName, 80);  

    /*
    while (Fgets(buf, MAXLINE, stdin) != NULL) {
	
	Rio_writen(clientfd, buf, strlen(buf));
	Rio_readlineb(&rio, buf, MAXLINE);
	Fputs(buf, stdout);
    }
    */

    int test1 = fread(fileBuf, sizeof(unsigned char), MAXFILESIZE, stdin);
    printf("read byte amnt: %i\n", test1);
    test1+=1;
    rio_writen(clientfd, &test1, 4);
    Rio_writen(clientfd, fileBuf, test1);

    Close(clientfd); //line:netp:echoclient:close
    exit(0);
}
