/*PRODUCERS.CPP*/
#include "factory_controller.h"
#include "producers.h"
#include "struct.h"

using namespace std;

/*Produces candies*/
void *producers(void *_args) {
	struct thread_args *args = (struct thread_args *) _args;

	/*
	* Save product ID to this producer and increment
	* Critical Section to prevent two Frog producers
	*/
	sem_wait(&args->setup);
	int _product_id = args->product_id++;
	sem_post(&args->setup);

	/*
	* Keep looping until goal is produced.
	* One closer to goal per loop.
	*/
	while (!sem_trywait(&args->goal)) {
		sem_wait(&args->available_space);	/*Checks for available space on belt*/

		/*
		* Checks if less than 3 frog bites.
		* If true, produce.
		* If false, return to top of while loop to ensure goal hasn't been reached yet.
		*/
		if (_product_id == 0) {
			if (sem_trywait(&args->frog_bites)) {
				/*Can't insert frog, refund goal count*/
				sem_post(&args->goal);
				continue;
			}
		}

		sem_wait(&args->belt_access);		/*Enter Critical Section*/
		push(_product_id, args->belt);		/*Add to belt*/
		sem_post(&args->unconsumed);		/*Inform consumer*/
		sem_post(&args->belt_access);		/*Exit Critical Section*/
		/*Sleep if flagged*/
		if (args->flag_f == 1 && _product_id == 0)
			usleep(args->f_val);
		else if (args->flag_e == 1 && _product_id == 1)
			usleep(args->e_val);
	}
}