/*MAIN.CPP*/
#include "factory_controller.h"
#include "consumers.h"
#include "producers.h"
#include "struct.h"

using namespace std;

int main(int argc, char *argv[]) {
	struct thread_args *args = (thread_args *)malloc(sizeof(struct thread_args));

	/*Instantiate values for args*/
	int goal = 100;
	sem_init(&args->goal, 0, goal);				/*Produce 100 candies*/
	sem_init(&args->unconsumed, 0, 0);			/*Number of unconsumed candies on belt*/
	sem_init(&args->frog_bites, 0, 3);			/*Max 3 frog bites on belt*/
	sem_init(&args->available_space, 0, 10);	/*Max 10 candies on belt*/
	sem_init(&args->belt_access, 0, 1);			/*Critical region*/
	sem_init(&args->setup, 0, 1);				/*To prevent duplicates*/
	args->amt_consumed = goal;	/*Consume all candies*/
	args->product_id = 0;		/*Product_ID: 0 = frog, 1 = escargot*/
	args->consumer_id = 0;		/*Consumer_ID: 0 = Lucy, 1 = Ethel*/
	args->flag_E = 0;
	args->flag_L = 0;
	args->flag_f = 0;
	args->flag_e = 0;
	args->belt = new queue<Candy*>;

	/*Flag handler*/
	/*Each flag slows a producer or consumer by n milliseconds*/
	int opt;
	while ((opt = getopt(argc, argv, "E:L:f:e:")) != -1) {
		switch (opt) {
			/*Multiply values by 1000 to convert to micro for usleep*/
		case 'E':
			args->E_val = atoi(optarg) * 1000;
			args->flag_E = 1;
			break;
		case 'L':
			args->L_val = atoi(optarg) * 1000;
			args->flag_L = 1;
			break;
		case 'f':
			args->f_val = atoi(optarg) * 1000;
			args->flag_f = 1;
			break;
		case 'e':
			args->e_val = atoi(optarg) * 1000;
			args->flag_e = 1;
			break;
		default:
			fprintf(stderr, "Usage: %s [-E msecs] [-L msecs] [-f msecs] [-e msecs] name\n", argv[0]);
			exit(EXIT_FAILURE);
		}
	}

	pthread_t frog_producer;
	pthread_t escargot_producer;
	pthread_t lucy_consumer;
	pthread_t ethel_consumer;

	/*Create producer and consumer threads*/
	pthread_create(&frog_producer, NULL, producers, args);
	pthread_create(&escargot_producer, NULL, producers, args);
	pthread_create(&lucy_consumer, NULL, consumers, args);
	pthread_create(&ethel_consumer, NULL, consumers, args);

	/*Ensure all threads are finished before continuing*/
	pthread_join(frog_producer, NULL);
	pthread_join(escargot_producer, NULL);
	pthread_join(lucy_consumer, NULL);
	pthread_join(ethel_consumer, NULL);

	print_report();
	free(args);
}
