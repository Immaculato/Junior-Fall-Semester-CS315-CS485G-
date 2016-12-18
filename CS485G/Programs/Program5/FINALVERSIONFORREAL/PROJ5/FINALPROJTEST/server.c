#include "csapp.h"

#include <stdio.h>
#include <stdlib.h>


#define MAX_NAME 80
#define MAX_SIZE 100*1024
#define MAX_FILES 40
#define KEY_BYTES 4
#define ERROR -1

int retval; //global error return value, set by whatever the most recent error is

struct myFile {
	int availible;
	char* nameOfFile;
	char* fileContent;
	int fileSize;
};

struct myFile allFiles[MAX_FILES];

void sendError(int response, int connectfd){

	int error = htonl(ERROR);
	int zero = 0;

	if( response != 0 ){
		Rio_writen(connectfd, &error, KEY_BYTES); 
	}

	else
		Rio_writen(connectfd, &zero , KEY_BYTES);

}

void clearFiles() {
	int i;
	for (i=0; i<MAX_FILES; i++) {
		allFiles[i].availible = 1;
	}
}

int mcput(char * filename, int connectfd, int datalen, rio_t * rio){

	//-1 is error code for too large of a file
	if (datalen > MAX_SIZE){
		sendError(-1, connectfd);
		return -1;
	}

	int availibleFileIndex = 0; // this is used later to save the file
	while (availibleFileIndex < MAX_FILES && !allFiles[availibleFileIndex].availible) availibleFileIndex+=1;	
	//if we have no available files, return error code -2.
	if (availibleFileIndex == MAX_FILES) {
		sendError(-1, connectfd);
		return -2;
	}

	int i = -1;
	int matchfound = 0;
	while (i < MAX_FILES && !matchfound){
		i++;
		//check if filename already already exists.
		if( allFiles[i].nameOfFile != NULL)
			if( strcmp(allFiles[i].nameOfFile, filename) ==0) matchfound = 1;		 
	}
	//If i is less than the maximum values of files we can have, then we have found a matching filename; we should write there according to spec 
	if(i<MAX_FILES) {
		free(allFiles[i].nameOfFile);
		free(allFiles[i].fileContent);
		availibleFileIndex = i;
	}
	//Send the A-OK
	sendError(0, connectfd);
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

	/*
	for(i = 0; i < datalen ; i++){
		printf("%c", file[i]);
	}
	*/

	//we allocate the 80 bytes for the filename here, and copy it over.
	char* finalFileName = (char *) malloc(MAX_NAME);
	memcpy(finalFileName, filename, MAX_NAME);
	
	//set the file slot to the newly input file
	allFiles[availibleFileIndex].availible = 0;
	allFiles[availibleFileIndex].nameOfFile = finalFileName;
	allFiles[availibleFileIndex].fileContent = file;
	allFiles[availibleFileIndex].fileSize = datalen;
	//return 0 to indicate success
	return 0;	
}

int mcget(char * filename, int connectfd) {

	int i;

	for( i = 0; i < MAX_FILES; i ++){
		if( allFiles[i].nameOfFile != NULL)
			if( strcmp(allFiles[i].nameOfFile, filename) == 0) break;		 
	}

	//if the file cannot be found, send an error.
	if (i == MAX_FILES) {
		sendError(-1, connectfd);
		return -1;
	} else sendError(0, connectfd);

	char * fileBuf = allFiles[i].fileContent;

	unsigned int networkOrderSize = htonl(allFiles[i].fileSize);

        rio_writen(connectfd, &networkOrderSize, KEY_BYTES);
    
    //we must write it in chunks because only ~ 10000 bytes can be written at a time.
    int numBytes = allFiles[i].fileSize;
    int areBytesRemaining = 1;
    int offset = 0;
    while (areBytesRemaining) {
        if (numBytes>10000) rio_writen(connectfd, fileBuf+offset, 10000);
        else {
                rio_writen(connectfd, fileBuf+offset, numBytes);
                areBytesRemaining = 0;
        }
	offset+=10000;
        numBytes-=10000;
   	}

   	return 0;
}
int mcdel(char * filename, int connectfd){

	int i;

	for( i = 0; i < MAX_FILES; i ++){
		if( allFiles[i].nameOfFile != NULL)
			if( strcmp(allFiles[i].nameOfFile, filename) == 0) break;		 
	}
	if (i==MAX_FILES) {
		sendError(-1, connectfd);
		return -1;
	} else {
		sendError(0, connectfd);
	}

	free(allFiles[i].nameOfFile);
	free(allFiles[i].fileContent);
	allFiles[i].nameOfFile = NULL;
	allFiles[i].availible = 1;
	allFiles[i].fileSize = 0;

	return 0;

};


int mclist(int connectfd) {
	int i;
	int offset = 0;
	//mclist should never return an error
        sendError(0, connectfd);	
	char *fileNames = (char*) calloc(MAX_FILES, MAX_NAME);
	for (i=0; i<MAX_FILES; i++) {
		if (!allFiles[i].availible) {
			memcpy(fileNames+offset, allFiles[i].nameOfFile, MAX_NAME);
			offset+=MAX_NAME;
		}
	}
	rio_writen(connectfd, fileNames, MAX_FILES*MAX_NAME);
	free(fileNames);
	return 0;
}
		

int validate(int secretKey, int keyUser){
	int accept = 0;

	if ( (keyUser == secretKey)){
		//printf("VALID\n");
		accept = 1;
	};
	
	
	return accept;
}


void application(int connectfd, int secretKey ){
	unsigned int keyUser, typeRequest;
	char filename[MAX_NAME] = "NONE";
	unsigned int rawNetBytes = 0;
	unsigned int rawTypeReq = 0;
	unsigned int valid, inputLength, inputLengthHostOrder;
	
	//We store the various fields from Rio in here. Otherwise we would use the lowercase Rio_readinitb
	rio_t rioIn;

	Rio_readinitb(&rioIn, connectfd);
	
	Rio_readn(connectfd, &rawNetBytes, KEY_BYTES);
	keyUser = ntohl(rawNetBytes);
	printf("Secret Key = %u\n", keyUser);
	
	valid = validate(secretKey, keyUser);

	Rio_readn(connectfd, &rawTypeReq, KEY_BYTES);
	typeRequest = ntohl(rawTypeReq);
	char typeString[5];
	switch(typeRequest) {
		case 0: strncpy(typeString, "get", KEY_BYTES);
			break;
		case 1: strncpy(typeString, "put", KEY_BYTES);
			break;
		case 2: strncpy(typeString, "del", KEY_BYTES);
			break;
		case 3: strncpy(typeString, "list", 5);
			break;
		default: strncpy(typeString, "???", KEY_BYTES);
			 valid = 0;
			 break;
	}
	printf("Request Type = %s\n", typeString);	
	if(valid){
		switch(typeRequest){
			case 0:
				Rio_readnb(&rioIn, filename, MAX_NAME);
				retval = mcget(filename, connectfd);
				break;
			case 1:
				Rio_readn(connectfd, filename, MAX_NAME);
				Rio_readn(connectfd, &inputLength, KEY_BYTES);
				inputLengthHostOrder = ntohl(inputLength);
				retval = mcput(filename, connectfd, inputLengthHostOrder, &rioIn);
				break;
			case 2:
				Rio_readnb(&rioIn, filename, MAX_NAME);
				retval = mcdel(filename, connectfd);
				break;
			case 3:
				retval = mclist(connectfd);
				break;
			default:
				retval = -1;
				break;
		}	
	}
	printf("Filename = %s\n", filename);
	char operationStatus[8] = "success";
	if (!valid) {
		strncpy(operationStatus, "error", 6);
		//the instruction will not execute at all if the secret key is invalid.
		//therefore, we should send the failure code separately here.
		sendError(-1, connectfd);
	} else if (retval != 0) {
		//if we have an invalid return value, then the error will already have
		//been sent.
		strncpy(operationStatus, "error", 6);
	}
	printf("Operation Status = %s\n", operationStatus);
	printf("--------------------------\n");
	/*
	if (valid != 0) {
		printf("ERROR: Invalid secret key.\n");
	} else if (typeRequest == 1 && retval == -1) {
		printf("ERROR: File exceeds size limit of 100KB.\n");
	} else if (typeRequest == 1 && retval == -2) {
		printf("ERROR: File limit reached.\n");
	} else {
		printf("Success!\n");
	}
	*/

	return;

};

int main(int argc, char * argv[]){

	int connectfd;
	socklen_t lengthClient = sizeof(struct sockaddr_in);
	struct sockaddr_in clientAddr;
	//variables used to see connecting ip
	//struct hostent *hp;
	//char *haddrp;

	if(argc < 3){
		printf("Execution Error. Usage './myserver <PORT> <SECRETKEY>'. \n");
		return 1;
	}

	clearFiles(); //this initializes our file system by declaring all slots empty

	

	int openedfd;
	int port = atoi(argv[1]);
	int secretKey = atoi(argv[2]);
	//printf("Initialized Secret Key = %d\n", secretKey);

	//Starts listening for connections on the specified port.
	openedfd = Open_listenfd(port);
	//printf("Server waiting for connection... \n");

	//Infinite loop- we are always waiting on a connection.
	while(1){
		
		//Connects to the client it request is received
		connectfd = Accept(openedfd, (SA *) &clientAddr, &lengthClient);
	
		/*
		//From the echoserver on the csapp website...
		//determine the domain name and IP address of the client 
		hp = Gethostbyaddr((const char *)&clientAddr.sin_addr.s_addr, 
			   sizeof(clientAddr.sin_addr.s_addr), AF_INET);
		haddrp = inet_ntoa(clientAddr.sin_addr);
		printf("Connected to %s (%s)\n", hp->h_name, haddrp);
		*/	

		//Sends the information to function to determine if valid. If valid, executes.
		application(connectfd, secretKey);
		//printf("Closing Connection...\n");
		Close(connectfd);
	}

	
	//printf("You shouldn't be here! \n");
	return 0;
}
