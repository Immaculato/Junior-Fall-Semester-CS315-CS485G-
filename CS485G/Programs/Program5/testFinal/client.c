//take from the echoclient.c source 

#include "csapp.h"

int main(int argc, char **argv) 
{
    int clientfd, port, secretKey;
    char *host, buf[MAXLINE];
    rio_t rio;
    char data[16];   
    bzero(buf, MAXLINE);

    if (argc != 4) {
	fprintf(stderr, "usage: %s <host> <port> <key>\n", argv[0]);
	exit(0);
    }
    host = argv[1];
    port = atoi(argv[2]);
    secretKey = atoi(argv[3]);
   
    unsigned int networkSecretKey = htonl(secretKey);
    
    printf("%u\n" , networkSecretKey);

    clientfd = Open_clientfd(host, port);
    Rio_readinitb(&rio, clientfd);
    //sprintf(data, "%u", networkSecretKey);
    send(clientfd, &networkSecretKey, 4, 0);
    //Rio_writen(clientfd, data, sizeof(data));  
    //Fputs(data, stdout);

    while (Fgets(buf, MAXLINE, stdin) != NULL) {
	Rio_writen(clientfd, buf, strlen(buf));
	Rio_readlineb(&rio, buf, MAXLINE);
	Fputs(buf, stdout);
    }
    Close(clientfd); //line:netp:echoclient:close
    exit(0);
}
