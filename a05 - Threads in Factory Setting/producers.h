/*PRODUCERS.H*/
#ifndef PRODUCERS_H
#define PRODUCERS_H

#include <unistd.h>
#include <semaphore.h>

void *producers(void *_args);

#endif