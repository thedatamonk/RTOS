#include"stdio.h"  
#include"stdlib.h"  
#include"sys/types.h"  
#include"sys/socket.h"  
#include"string.h"  
#include"netinet/in.h"  
#include"netdb.h"
#include <arpa/inet.h>

#define ITERS 1000000
#define PORT 4444
#define BUF_SIZE 1
#define CHAR_LOW 33
#define CHAR_HIGH 126


int main(int argc, char**argv){
  struct sockaddr_in addr, client_addr;
  int sockfd, ret;
  char buffer;
  struct hostent * server;
  char *serverAddr;

  if (argc < 2){
    printf("usage: client < ip address >\n");
    exit(1);  
  }

  // this is the IP address of the machine in which the server is running
  serverAddr = argv[1];

  // creating a socket for the client
  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  if (sockfd < 0){
      printf("Error creating socket!\n");  
      exit(1);
  }

  printf("Socket created...\n");

  memset(&addr, 0, sizeof(addr));

  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr(serverAddr);
  addr.sin_port = PORT;

  // try connecting to the server
  ret = connect(sockfd, (struct sockaddr *) &addr, sizeof(addr));
  if (ret < 0){
      printf("Error connecting to the server!\n");  
      exit(1);
  }

  printf("Connected to the server...\n");

  memset(&buffer, 0, BUF_SIZE);


  int i=0;

  while(i<ITERS){
    buffer = (rand() % (CHAR_HIGH - CHAR_LOW + 1)) + CHAR_LOW; 

    ret = sendto(sockfd, &buffer, BUF_SIZE, 0, (struct sockaddr*)& addr, sizeof(addr));

    if (ret < 0){
      printf("Error sending data!\n\t-%c", buffer);
    }
  
    ret = recvfrom(sockfd, &buffer, BUF_SIZE, 0, NULL, NULL);  
    if (ret < 0) {  
      printf("Error receiving data!\n");    
    }else{
      printf("Received: %c", buffer);
      // fputs(buffer, stdout);
      printf("\n");
    }  

    i++;
  }


  return 0;

}