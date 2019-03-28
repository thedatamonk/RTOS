#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

int diceVal;
sem_t locks[2];

void *play(void* player_lock){

	sem_wait(player_lock);
	
	// generate a random number between 1 to 6
	diceVal = (rand() % 6) + 1;
}

int main(){
	pthread_t p[2];
	struct timeval stop, start;

	int score[2] = {0, 0};

	gettimeofday(&start, NULL);
	do{
		pthread_create(&p[0], NULL, play, (void*)&locks[0]);
		pthread_create(&p[1], NULL, play, (void*)&locks[1]);

		sem_post(&locks[0]);
		pthread_join(p[0], NULL);
		score[0] +=diceVal;

		sem_post(&locks[1]);
		pthread_join(p[1], NULL);
		score[1] += diceVal;

		printf("Player 1: %d\t Player 2: %d\n", score[0], score[1]);

	}while((score[0] < 5000) && (score[1] < 5000));

	gettimeofday(&stop, NULL);

	if (score[0]>5000)
		printf("Winner is Player 1 with score %d\n", score[0]);
	
	if (score[1]>5000)
		printf("Winner is Player 2 with score %d\n", score[1]);


	printf("Total time (seconds): %lu\n", stop.tv_usec - start.tv_usec);

	return 0;
}