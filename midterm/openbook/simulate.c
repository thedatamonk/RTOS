#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include  <stdlib.h>
#include <string.h>

char string[1024];
sem_t lock;

int isSubstring(char* s1, char* s2) 
{ 
    int M = strlen(s1); 
    int N = strlen(s2); 
  
    /* A loop to slide pat[] one by one */
    for (int i = 0; i <= N - M; i++) { 
        int j; 
  
        /* For current index i, check for pattern match */
        for (j = 0; j < M; j++) 
            if (s2[i + j] != s1[j]) 
                break; 
  
        if (j == M) 
            return 1; 
    } 
  
    return -1; 
} 

void *searchPrefix(void* prefix){

	printf("Searching prefix: %s\n", (char*)prefix);
	printf("Waiting for user to enter string [max 1024 chars]\n");
	sem_wait(&lock);

	if (isSubstring(prefix, string) == 1)
		printf("Yes prefix \"%s\" is present in \"%s\"\n", (char*)prefix, string);
	else
		printf("Prefix not found!\n");
}

void main(){

	pthread_t tr;
	int check;
	char prefix[1024];

	printf("Enter the prefix string [max 1024 characters]\n");
	scanf("%s", prefix);


	do{
		//thread created  and started here 
		pthread_create(&tr, NULL, searchPrefix, (void*)prefix);

		scanf(" %[^\n]s", string);

		sem_post(&lock);
		pthread_join(tr, NULL);

		printf("Do you want to continue: (1 for YES; 0 for NO)\n");
		scanf("%d", &check);

	} while(check==1);

	exit(0);
}