#include "csapp.h"

#include <stdio.h>
#include <stdlib.h>


#define MAX_NAME 80
#define MAX_SIZE 100*1024
#define MAX_FILES_SIZE 40*100*1024
#define KEY_BYTES 4

int allFiles[MAX_FILES_SIZE];
int retval; //global error return value, set by whatever the most recent error is

int mcput(char * filename, int connectfd, char * data, int datalen){

	int fd;
	printf("RECEIVED FILENAME: %s\n", filename);
	printf("RECEIVED FILE LENGTH: %d\n", datalen);
	

	int n;
	rio_t rio;
 	char buf[MAXLINE];

	
	return 0;	
}

int mcget(char * filename, int connectfd, int datalen);
void deleteFile();
void listFiles();
int validate(int secretKey, int keyUser){
	int accept = 1;

	if ( (keyUser == secretKey)){
		printf("VALID\n");
		accept = 0;
	};
	
	
	return accept;
}


void application(int connectfd, int secretKey ){
	unsigned int keyUser, typeRequest;
	char filename[MAX_NAME];
	char data[MAX_SIZE];
	unsigned int rawNetBytes = 0;
	unsigned int rawTypeReq = 0;
	char *rawInput;
	int valid, inputLength, inputLengthHostOrder;
	//We store the various fields from Rio in here. Otherwise we would use the lowercase Rio_readinitb
	rio_t rioIn;

	Rio_readinitb(&rioIn, connectfd);
	
	Rio_readnb(&rioIn, &rawNetBytes, 4);
	keyUser = ntohs(rawNetBytes);
	printf("Secret Key: %u\n", keyUser);
	
	valid = validate(secretKey, keyUser);

	Rio_readnb(&rioIn, &rawTypeReq, 4);
	typeRequest = ntohs(rawTypeReq);
	printf("Request: %u\n", typeRequest);

	Rio_readnb(&rioIn, filename, 80);
	printf("Filename: %s\n", filename);
	if(valid == 0){
		switch(typeRequest){
			case 1: 
				Rio_readnb(&rioIn, data, MAX_SIZE);
				Rio_readnb(&rioIn, &inputLength, 4);
				inputLengthHostOrder = ntohs(inputLength);
				retval = mcput(filename, connectfd, data, inputLengthHostOrder);
				break;
			default:
				retval = -1;
				break;
		}	
	}
	if (retval != 0 && valid != 0)
		printf("FAILURE\n");
	else
		printf("SUCCESS\n");

	return;

};

int main(int argc, char * argv[]){

	int connectfd;
	socklen_t lengthClient = sizeof(struct sockaddr_in);
	struct sockaddr_in clientAddr;
	char type, filename, status;
	struct hostent *hp;
	char *haddrp;

	if(argc < 3){
		printf("Execution Error. Usage './myserver <PORT> <SECRETKEY>'. \n");
		return 1;
	}
	

	int openedfd;
	int port = atoi(argv[1]);
	int secretKey = atoi(argv[2]);
	printf("Inialized Secret Key = %d\n", secretKey);

	//Starts listening for connections on the specified port.
	openedfd = Open_listenfd(port);
	printf("Server waiting for connection... \n");

	//Infinite loop- we are always waiting on a connection.
	while(1){
		
		//Connects to the cliet it request is received
		connectfd = Accept(openedfd, (SA *) &clientAddr, &lengthClient);
	
		//From the echoserver on the csapp website...
		/* determine the domain name and IP address of the client */
		hp = Gethostbyaddr((const char *)&clientAddr.sin_addr.s_addr, 
			   sizeof(clientAddr.sin_addr.s_addr), AF_INET);
		haddrp = inet_ntoa(clientAddr.sin_addr);
		printf("Connected to %s (%s)\n", hp->h_name, haddrp);
	
		//Sends the information to function to determine if valid. If valid, executes.
		application(connectfd, secretKey);
		printf("Closing Connection...\n");
		Close(connectfd);
	}

	
	printf("You shouldn't be here! \n");
	return 0;
}
