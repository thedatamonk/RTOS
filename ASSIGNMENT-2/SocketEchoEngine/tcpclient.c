#include"stdio.h"  
#include"stdlib.h"  
#include"sys/types.h"  
#include"sys/socket.h"  
#include"string.h"  
#include"netinet/in.h"  
#include"netdb.h"
#include <arpa/inet.h>
#include <time.h>

#define ITERS 1000
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
  clock_t start, end, start_per_req;

  double total_time_elapsed, avg_response_time=0.0;

  if (argc < 2){
    printf("usage: server < ip address >\n");
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

  // connecting the socket to the server IP address
  ret = connect(sockfd, (struct sockaddr *) &addr, sizeof(addr));
  if (ret < 0){
      printf("Error connecting to the server!\n");  
      exit(1);
  }

  printf("Connected to the server...\n");

  memset(&buffer, 0, BUF_SIZE);


  int t_step = 0;

  start = clock();

  while(t_step < ITERS){

    // generating a random alphanumeric character
    buffer = (rand() % (CHAR_HIGH - CHAR_LOW + 1)) + CHAR_LOW; 


    start_per_req = clock();

    // send the character to the server IP address
    ret = sendto(sockfd, &buffer, BUF_SIZE, 0, (struct sockaddr*)& addr, sizeof(addr));
    
    if (ret < 0){
      printf("Error sending data!\n\t-%c", buffer);
    }else{
      printf("Character sent to server IP (%s) is: %c\n", serverAddr, buffer);
    }

    //noe the client receives the data from server through the socket
    ret = recvfrom(sockfd, &buffer, BUF_SIZE, 0, NULL, NULL);  
    if (ret < 0) {  
      printf("Error receiving data!\n");    
    }else{

      avg_response_time += ((double) (clock()-start_per_req) / (CLOCKS_PER_SEC / 1000));

      printf("Received converted character from server: %c\n\n", buffer);
    }  

    t_step++;
  }

  end = clock();

  total_time_elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;

  avg_response_time /= ITERS;

  printf ("Client finished %d requests in %.2f seconds\n", ITERS, total_time_elapsed);
  printf ("Average Response time: %f milliseconds\n\n", avg_response_time);



  exit(0);

}