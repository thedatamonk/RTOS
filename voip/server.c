#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include"stdio.h"
#include"stdlib.h"
#include"sys/types.h"
#include"sys/socket.h"
#include"string.h"
#include"netinet/in.h"
#include<unistd.h>
#include <arpa/inet.h>
#include <ctype.h>



#include <pulse/simple.h>
#include <pulse/error.h>
#include <pulse/gccmacro.h>
#define PORT 4444
#define BUF_SIZE 10000
#define CLADDR_LEN 100




void main(int argc, char const *argv[]) {
 struct sockaddr_in addr, cl_addr;
 int sockfd, len, rett, newsockfd;
 char buffer[BUF_SIZE];
 pid_t childpid;
 char clientAddr[CLADDR_LEN];

 

 static const pa_sample_spec ss = {
        .format = PA_SAMPLE_S16LE,
        .rate = 44100,
        .channels = 2
        };

        pa_simple *s = NULL;
        int ret = 1;
        int error;
 

if (!(s = pa_simple_new(NULL, argv[0], PA_STREAM_PLAYBACK, NULL, "playback", &ss, NULL, NULL, &error))) {
            fprintf(stderr, __FILE__": pa_simple_new() failed: %s\n", pa_strerror(error));
            
        }     


 sockfd = socket(AF_INET, SOCK_STREAM, 0);
 if (sockfd < 0) {
  printf("Error creating socket!\n");
  exit(1);
 }
 printf("Socket created...\n");
 
 memset(&addr, 0, sizeof(addr));
 addr.sin_family = AF_INET;
 addr.sin_addr.s_addr = INADDR_ANY;
 addr.sin_port = PORT;
 
 rett = bind(sockfd, (struct sockaddr *) &addr, sizeof(addr));
 if (rett < 0) {
  printf("Error binding!\n");
  exit(1);
 }
 printf("Binding done...\n");

 printf("Waiting for a connection...\n");
 listen(sockfd, 5);

 for (;;) { //infinite loop
  len = sizeof(cl_addr);
  newsockfd = accept(sockfd, (struct sockaddr *) &cl_addr, &len);
  if (newsockfd < 0) {
   printf("Error accepting connection!\n");
   exit(1);
  }
  printf("Connection accepted...\n");

   

   for (;;) {
    
        uint8_t buf[BUF_SIZE];
        rett = recvfrom(newsockfd, &buf, BUF_SIZE, 0, (struct sockaddr *) &cl_addr, &len);
        if(rett < 0) {
         printf("Error receiving data!\n");  
         exit(1);
        }
        else {
        
          while(1){
                        
                        ssize_t r;
                          if ((r = read(newsockfd, buf, sizeof(buf))) <= 0) {
                          if (r == 0) /* EOF */
                              break;              
                      }
                      
                     
                          if (pa_simple_write(s, buf, sizeof(buf), &error) < 0) {
                              fprintf(stderr, __FILE__": pa_simple_write() failed: %s\n", pa_strerror(error));
                              
                          }
                      //}
                  }



          }  





        
}
  
  }
  close(newsockfd);
 }

