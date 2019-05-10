#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h> 
#include "worker.h"

void main() {
	pthread_t thread[5];
	int nums[5];
	int i;

	//Create five threads
	for (i = 0; i < 5; i++) {
		nums[i] = i;
		pthread_create(&thread[i], NULL, worker, &nums[i]);
		//pthread_join(thread[i], NULL); 
		//Put ^this here to have threads run one at a time
	}
	//Ensure all threads are finished before continuing
	for (i = 0; i < 5; i++)
		pthread_join(thread[i], NULL);

	//All threads completed
	printf("work complete\n");
}