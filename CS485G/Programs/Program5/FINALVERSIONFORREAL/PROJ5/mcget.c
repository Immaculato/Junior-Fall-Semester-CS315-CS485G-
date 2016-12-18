//take from the echoclient.c source 

#include "csapp.h"
#define MAXFILENAME 80
#define INTBYTES 4
int main(int argc, char **argv) 
{
    unsigned int clientfd, port, secretKey, errorNetwork, networkDataLen, type;
    char *host, buf[MAXLINE], * file;
    rio_t rio;
    char fileName[MAXFILENAME];   
    bzero(buf, MAXLINE);
    int datalen, error;

    if (argc != 5) {
	fprintf(stderr, "usage: %s <host> <port> <key> <filename>\n", argv[0]);
	exit(0);
    }
    host = argv[1];
    port = atoi(argv[2]);
    secretKey = atoi(argv[3]);
    strncpy(fileName, argv[4], MAXFILENAME);
    type = 0; 
	
    unsigned int networkOrderType = htonl(type);
    unsigned int networkSecretKey = htonl(secretKey);
     
    clientfd = Open_clientfd(host, port);
    Rio_readinitb(&rio, clientfd);
  
    rio_writen(clientfd, &networkSecretKey, INTBYTES); 
    rio_writen(clientfd, &networkOrderType, INTBYTES);
    rio_writen(clientfd, &fileName, MAXFILENAME);  

    Rio_readnb(&rio, &errorNetwork, INTBYTES);
    error = ntohl(errorNetwork);

    if ( error != 0 ) {
        printf("Error\n");
	return -1;
    }

    rio_readnb(&rio, &networkDataLen, INTBYTES);
    datalen = ntohl(networkDataLen);
        //we send in chunks of 10,000 bytes, so read those appropriately.
        file = (char *) malloc(datalen);

        int areBytesRemaining = 1;
        int offset = 0;
        int remainingBytes = datalen;
        while (areBytesRemaining) {
                if (remainingBytes > 10000) rio_readnb(&rio, file+offset, 10000);
                else {
                        rio_readnb(&rio, file+offset, remainingBytes);
                        areBytesRemaining = 0;
                }
                offset+=10000;
                remainingBytes-=10000;
        }
        int i;
        for(i = 0; i < datalen ; i++){
                printf("%c", file[i]);
        }

    Close(clientfd); //line:netp:echoclient:close
    exit(0);
}
