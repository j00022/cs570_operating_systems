#include "worker.h"

void *worker(void *input) {
	int *num = (int *)input;
	int squared = *num * *num;
	printf("%d\n", squared);
}