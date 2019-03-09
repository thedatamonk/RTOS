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


#define PORT 4444
#define BUF_SIZE 1000
#define FILE_NAME_LENGTH 30
#define FILE_NOT_EXISTS "File doesn't exists"
#define NUM_FILES 100
#define DB_PATH "./db/"

int main(int argc, char**argv){
  struct sockaddr_in addr, client_addr;
  int sockfd, ret;
  char buffer[BUF_SIZE];
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


  // create an array of strings that will contain the file names
  char db[NUM_FILES][FILE_NAME_LENGTH];

  // to store current directory in currentPath

  DIR *dr;
  struct dirent *de; // pointer for directory entry
  struct stat buf;

    
  // Open Current Directory
  if ((dr = opendir(DB_PATH)) == NULL){
      printf("Could not open database directory\n");
      return errno;
  }


  // add filnames of the DB in a C-Array
  int i=0;
  while ((de = readdir(dr)) != NULL){
        
      /*Skips . and ..*/
      if(strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0)
            continue;
        
      char fullPath[FILENAME_MAX] = "";
        
      strcat(fullPath, DB_PATH);
      strcat(fullPath, de->d_name);

      if (stat(fullPath, &buf) == -1){
          perror("stat");
          return errno;
      }


      if (S_ISREG(buf.st_mode)){
          // only append to the list when it's a regular file
          strcpy(db[i], fullPath);
          i++;
      }
  }

  closedir(dr);

  i = 0;
  
  while(i<NUM_FILES){

      strcpy(buffer, db[i]);

      int length = strlen (buffer);
       
      if (buffer[length - 1] == '\n')
          buffer[length - 1] = '\0';

      
      // send message to server

      ret = sendto(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr* )&addr, sizeof(addr));
      
      if (ret < 0){
        printf("Error sending data!\n\t-%s", buffer);
      }       

      ret = recvfrom(sockfd, buffer, BUF_SIZE, 0, NULL, NULL);

      if (ret < 0){
        printf("Error receiving data!\n");
      }else{
        printf("Received: %s", buffer);
        printf("\n");
      }

      i++;

  }

  return 0;

}