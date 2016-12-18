#include "csapp.h"

#include <stdio.h>
#include <stdlib.h>


#define MAX_NAME 80
#define MAX_SIZE 100*1024
#define MAX_FILES 40
#define KEY_BYTES 4

int retval; //global error return value, set by whatever the most recent error is

struct myFile {
	int availible;
	char* nameOfFile;
	char* fileContent;
};

struct myFile allFiles[MAX_FILES];

void clearFiles() {
	int i;
	for (i=0; i<40; i++) {
		allFiles[i].availible = 1;
	}
}

int mcput(char * filename, int connectfd, int datalen, rio_t * rio){

	int fd;
	printf("RECEIVED FILENAME: %s\n", filename);
	printf("RECEIVED FILE LENGTH: %d\n", datalen);
	//-1 is error code for too large of a file
	if (datalen >= MAX_SIZE) return -1;

	int availibleFileIndex = 0; // this is used later to save the file
	while (availibleFileIndex < 40 && !allFiles[availibleFileIndex].availible) availibleFileIndex+=1;	
	//if we have no availible files, return error code -2.
	if (availibleFileIndex == 40) return -2;


	//int timesToGrab = datalen / MAXLINE + 1; //This determines the number of times we will have to read

	//mallocs the size of the file passed into the function
	char *file;
	//we send in chunks of 10,000 bytes, so read those appropriately.
	file = (char *) malloc(datalen);
	
	int areBytesRemaining = 1;
	int offset = 0;
	int remainingBytes = datalen;
	while (areBytesRemaining) {
		if (remainingBytes > 10000) rio_readnb(rio, file+offset, 10000);
		else {
			rio_readnb(rio, file+offset, remainingBytes);
			areBytesRemaining = 0;
		}
		offset+=10000;
		remainingBytes-=10000;
	}
	int i;
	for(i = 0; i < datalen ; i++){
		printf("%c", file[i]);
	}

	//we allocate the 80 bytes for the filename here, and copy it over.
	char* finalFileName = (char *) malloc(80);
	memcpy(finalFileName, filename, 80);
	
	//set the file slot to the newly input file
	allFiles[availibleFileIndex].availible = 0;
	allFiles[availibleFileIndex].nameOfFile = finalFileName;
	allFiles[availibleFileIndex].fileContent = file;
	//return 0 to indicate success
	return 0;	
}

int mcget(char * filename, int connectfd, int datalen) {

}
void deleteFile();
int mclist(int connectfd) {
	int i;
	int offset = 0;
	char *fileNames = (char*) calloc(40, 80);
	for (i=0; i<40; i++) {
		if (!allFiles[i].availible) {
			memcpy(fileNames+offset, allFiles[i].nameOfFile, 80);
			offset+=80;
		}
	}
	rio_writen(connectfd, fileNames, 40*80);
	free(fileNames);
	return 0;
}
		

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

	if(valid == 0){
		switch(typeRequest){
			case 1:
				Rio_readnb(&rioIn, filename, 80);
				printf("Filename: %s\n", filename);
				Rio_readnb(&rioIn, &inputLength, 4);
				inputLengthHostOrder = ntohs(inputLength);
				retval = mcput(filename, connectfd, inputLengthHostOrder, &rioIn);
				break;
			case 3:
				retval = mclist(connectfd);
			default:
				retval = -1;
				break;
		}	
	}
	if (valid != 0) {
		printf("ERROR: Invalid secret key.\n");
	} else if (typeRequest == 1 && retval == -1) {
		printf("ERROR: File exceeds size limit of 100KB.\n");
	} else if (typeRequest == 1 && retval == -2) {
		printf("ERROR: File limit reached.\n");
	} else {
		printf("Success!\n");
	}

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

	clearFiles(); //this initializes our file system by declaring all slots empty

	

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
