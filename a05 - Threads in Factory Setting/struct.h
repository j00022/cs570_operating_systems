/*STRUCT.H*/
#ifndef STRUCT_H
#define STRUCT_H

#include <pthread.h> 
#include <semaphore.h>
#include "factory_controller.h"

struct thread_args {
	sem_t goal, unconsumed, frog_bites, available_space, belt_access, setup;
	int consumer_id, product_id, amt_consumed;
	int flag_E, flag_L, flag_f, flag_e;
	int E_val, L_val, f_val, e_val;
	std::queue<Candy*> *belt;
};

#endif