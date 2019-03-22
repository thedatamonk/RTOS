#include <stdio.h>
#include <stdlib.h>
#include  "sys/types.h"
#include  "sys/socket.h"
#include "string.h"
#include "netinet/in.h"
#include <unistd.h>
#include <arpa/inet.h>
#include  <ctype.h>
#include  <time.h>


#define PORT 4444				// port number
#define FILE_NAME_LENGTH 50		// length of the filname string
#define CLADDR_LEN 100			// len of the client address
#define BUF_SIZE 1024			//size of the buffer that will be written into
#define NUM_FILES 5				//number of files being written to by the sensors
#define TIMESIZE 50				//size of the timestring

void main(){
	
	struct sockaddr_in addr, cl_addr;
	int i, sockfd, len, ret, newsockfd;

	char clientAddr[CLADDR_LEN], buffer[BUF_SIZE]="", MY_TIME[TIMESIZE];
	char filenames[NUM_FILES][FILE_NAME_LENGTH] = {"sensor1.txt", 
													"sensor2.txt",
													"sensor3.txt",
													"sensor4.txt",
													"sensor5.txt"};

	pid_t childpid;
	FILE* fptr;

	time_t t; struct tm* tmp;

	//  create a socket for the server
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0){
		printf("Error creating socket!\n");
		exit(1);
	}

	printf("Socket created...\n");

	//adding option to the socket created
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = PORT;

	// bind the server to the socket
	ret = bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));

	if (ret < 0){
		printf("Error binding!\n");
		exit(1);
	}

	printf("Binding done...\n");

	printf("Waiting for a connection...\n");
	
	// maximum number of outstanding connection in the socket queue
	
	///server listening through socket for connections 
	listen(sockfd, 5);

	//main loop where the server continuously receives requests from the clients

	while(1){



		len = sizeof(cl_addr);

		//accept a new client request
		newsockfd = accept(sockfd, (struct sockaddr*)&cl_addr, &len);

		if (newsockfd < 0){
			printf("Error accepting connection!\n");
			exit(1);
		}

		printf("Connection accepted...\n");

		inet_ntop(AF_INET,  &(cl_addr.sin_addr), clientAddr, CLADDR_LEN);

		if ((childpid = fork()) == 0){
			//creating a child process
			close(sockfd);

			// stop listening for new connections by the main process.
			// the child will continue to listen.
			// the main process now handles the connected client

			while(1){
				memset(buffer, 0, BUF_SIZE);

				ret = recvfrom(newsockfd, buffer, BUF_SIZE, 0, (struct sockaddr *) &cl_addr, &len);

				if (ret < 0){
					printf("Error receiving data!\n");
					exit(1);
				}

				printf("Data request received from client [%s]\n", clientAddr);

				//opening and reading from the sensor files

				char res [1024];
				int res_counter = 0;

				time(&t);

				tmp = localtime(&t);

				strftime(MY_TIME, sizeof(MY_TIME), "%Y-%m-%d %H:%M:%S", tmp);
				strcat(buffer, MY_TIME);
				strcat(buffer, ",");

				for (i=0; i<NUM_FILES; i++){
					fptr = fopen(filenames[i], "r");

					while((res[res_counter++] = fgetc(fptr)) != EOF);
					res[res_counter-1] = ',';
					fclose(fptr);
				}

				res[res_counter-1] = '|';
				res[res_counter++] = '\0';

				strcat(buffer, res);

				// after preparing the data we have to send it back to the server
				printf("String: %s\n", buffer);
				ret = sendto(newsockfd, buffer, BUF_SIZE, 0, (struct sockaddr*)&cl_addr, len);

				if(ret < 0){
					printf("Error sending data!\n");
					exit(1);
				}

				printf("Sensor data sent to client[%s]\n", clientAddr);


			}

		}

		close(newsockfd);
	} 

}