#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

int diceVal;
sem_t locks[2];
int snakes[7] = {5, 10, 15, 20, 25, 30, 35};

void *play(void* player_lock){

	int choice;
	sem_wait(player_lock);
	
	// generate a random number between 1 to 6
	diceVal = (rand() % 6) + 1;

	choice = (rand() % 8) + 1; // 8 corresponds to 7 snakes + 1 no snake in the game

	if (choice < 8)
		diceVal -= snakes[choice-1];
}

int main(){
	pthread_t p[2];
	struct timeval stop, start;
	srand(time(0)); 
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

	}while((score[0] < 100) && (score[1] < 100));

	gettimeofday(&stop, NULL);

	if (score[0]>=100)
		printf("Winner is Player 1 with score %d\n", score[0]);
	
	if (score[1]>=100)
		printf("Winner is Player 2 with score %d\n", score[1]);


	printf("Total time (microseconds): %lu\n", stop.tv_usec - start.tv_usec);

	return 0;
}