/*CONSUMERS.CPP*/
#include "factory_controller.h"
#include "consumers.h"
#include "struct.h"

using namespace std;

/*Consumes candies.*/
void *consumers(void *_args) {
	struct thread_args *args = (struct thread_args *) _args;

	/*
	* Set consumer to consumer ID
	* Critical Section to prevent two Lucys
	*/
	sem_wait(&args->setup);
	string consumer_name;
	int _consumer_id = args->consumer_id++;
	if (_consumer_id == 0)
		consumer_name = "Lucy";
	else if (_consumer_id == 1)
		consumer_name = "Ethel";
	sem_post(&args->setup);		/*Exit Critical Section*/

	/*
	* Keep looping until producer's goal is reached
	* And there is nothing left to be consumed.
	* Each loop will consume an item if available.
	*/
	while (args->amt_consumed != 0) {
		while (!sem_trywait(&args->unconsumed)) {
			sem_wait(&args->belt_access);		/*Enter Critical Section*/
			/*Remove candy from belt*/
			int prod_id = pop(consumer_name, args->belt); /*Remove from belt*/
			if (prod_id == 0) {					/*If frog bite was removed...*/
				sem_post(&args->frog_bites);	/*Inform frog producer*/
			}
			sem_post(&args->available_space);	/*Inform producer*/
			args->amt_consumed--;
			sem_post(&args->belt_access);		/*Exit Critical Section*/
			/*Sleep if flagged*/
			if (args->flag_L == 1 && _consumer_id == 0)
				usleep(args->L_val);
			else if (args->flag_E == 1 && _consumer_id == 1)
				usleep(args->E_val);
		}
	}
}
