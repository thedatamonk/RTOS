// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080 

int main(int argc, char const *argv[]) 
{ 
	// address of the  client
	struct sockaddr_in address;

	int sock = 0, valread; 
	
	// address of the server
	struct sockaddr_in serv_addr;


	char *hello = "Hello from client2"; 
	char buffer[1024] = {0}; 
	
	// creating a socket
	// AF_INET means Ipv4 protocol,  and AF_INET6 means Ipv6 protocol 
	// SOCK_STREAM means communication type (SOCK_STREAM = TCP)
	// 0 specifies internet protocol value which is 0

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){ 
		printf("\n Socket creation error \n"); 
		return -1; 
	} 

	// to fill the memory starting from &serv_addr upto sizeof (serv_addr) with zeros
	memset(&serv_addr, '0', sizeof(serv_addr)); 


	serv_addr.sin_family = AF_INET; 

	// convert PORT from host byte order to network byte order
	serv_addr.sin_port = htons(PORT); 
	
	// Convert IPv4 and IPv6 addresses from text to binary form 
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
	{ 
		printf("\nInvalid address/ Address not supported \n"); 
		return -1; 
	} 

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
	{ 
		printf("\nConnection Failed \n"); 
		return -1; 
	} 

	int i=0;
	while (i<1000000){
		send(sock , hello , strlen(hello) , 0); 
		printf("Hello message sent\n"); 
		valread = read( sock , buffer, 1024); 
		printf("%s\n",buffer ); 
	
		i++;
	}
	return 0; 
} 
