#include"stdio.h"  
#include"stdlib.h"  
#include"sys/types.h"  
#include"sys/socket.h"  
#include"string.h"  
#include"netinet/in.h"  
#include"netdb.h"
#include <sys/stat.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <time.h>

#define PORT 4444
#define BUF_SIZE 1024

int main(int argc, char** argv){
	struct sockaddr_in addr, client_addr;
	int sockfd, ret;
	char buffer[BUF_SIZE], *serverAddr;
	struct hostent* server;

	if (argc < 2){
		printf("usage: server < ip address >\n");
		exit(1);
	}

	FILE* csvfptr;
	//opening a file to write into


	//this is the IP address of the machine in which the server is running
	
	serverAddr = argv[1];

	//creating a socket for the client
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0){
		printf("Error creating socket!\n");
		exit(1);
	}	

	printf("Socket created...\n");

	memset(&addr, 0, sizeof(addr));

	//adding options for the  socket
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(serverAddr);
	addr.sin_port = PORT;

	// the client connect to the server socket
	ret = connect(sockfd, (struct sockaddr*)  &addr, sizeof(addr));

	if (ret < 0){
		printf("Error connecting to the server...\n");
		exit(1);
	}

	printf("Connected to the server...\n");


	// this is the main loop in wwhich client will periodically request
	// data from the server 
	while(1){
		
		if((csvfptr = fopen("csvfile.txt", "a"))==NULL){
			printf("File doesn't exists\n");
			exit(1);
		}

		//send a data request
		memset(&buffer, 0, BUF_SIZE);

		ret = sendto(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr*)&addr, sizeof(addr));

		if (ret < 0){
			printf("Error requesting data");
			exit(1);
		}else{
			printf("Client sent request to server\n");
		}

		//receive data from the server
		ret = recvfrom(sockfd, buffer, BUF_SIZE, 0, NULL, NULL);

		if (ret < 0){
			printf("Error while receiving data");
			exit(1);
		}

		// write the data into a csv file here
		printf("Data received from server: %s\n", buffer);
		fprintf(csvfptr, "%s\n", buffer);
		fclose(csvfptr);
				

		// to match the frequency of the sensors
		sleep(2);
	}


	exit(0);

}