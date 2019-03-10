#include"stdio.h"
#include"stdlib.h"
#include"sys/types.h"
#include"sys/socket.h"
#include"string.h"
#include"netinet/in.h"
#include <unistd.h>
#include <arpa/inet.h>
#include <ctype.h>

#define PORT 4444
#define BUF_SIZE 1
#define CLADDR_LEN 100

void main(){
	struct sockaddr_in addr, cl_addr;
	int sockfd, len, ret, newsockfd;

	char buffer;
	pid_t childpid;
	char clientAddr[CLADDR_LEN];

	//  create a socket for the server
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0){
		printf("Error creating socket!\n");
		exit(1);
	}

	printf("Socket created...\n");

	// setting IP address related information
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = PORT;

	// bind the server address to the socket 
	// through this socket the server will listen from client requests
	ret = bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));

	if (ret < 0){
		printf("Error binding!\n");
		exit(1);
	}

	printf("Binding done...\n");

	// now the server is waiting for requests from the client
	printf("Waiting for a connection...\n");
	
	// maximum number of outstanding connection in the socket queue : in this case it's 5
	listen(sockfd, 5);

	while(1){
		//infinite loop to keep the server running

		// length of client address
		len = sizeof(cl_addr);

		// accept a new client request
		// it creates a new socket descriptor (like file descriptor) and then the client can use this to communicate
		newsockfd = accept(sockfd, (struct sockaddr *) &cl_addr, &len);

		if (newsockfd < 0){
			printf("Error accepting connection!\n");
			exit(1);
		}
		printf("Connection accepted...\n");

		// convert client address from binary form to text form
		inet_ntop(AF_INET, &(cl_addr.sin_addr), clientAddr, CLADDR_LEN);

		
		//creating a child process

		if ((childpid = fork()) == 0){
			close(sockfd);

			// stop listening for new connections by the main process.
			// the child will continue to listen.
			// the main process now handles the connected client

			while(1){
				memset(&buffer, 0, BUF_SIZE);
				ret = recvfrom(newsockfd, &buffer, BUF_SIZE, 0, (struct sockaddr *) &cl_addr, &len);

				if (ret < 0){
					printf("Error receiving data!\n");
					exit(1);
				}

				printf("Received data from client at IP (%s): %c\n", clientAddr, buffer);

				// process the received data
				if (isalpha(buffer)){
         			if (isupper(buffer))
                		buffer  = tolower(buffer);
            	    else
                		buffer = toupper(buffer);
        		}
				

				ret = sendto(newsockfd, &buffer, BUF_SIZE, 0, (struct sockaddr *) &cl_addr, len);

				if (ret < 0){
					printf("Error sending data!\n");
					exit(1);
				}
				printf("Sent data to client at IP (%s): %c\n\n", clientAddr, buffer);

			}
		}

		close(newsockfd);
	}

}