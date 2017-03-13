#ifndef _QUEUE_H
#define _QUEUE_H

#include <pthread.h>

#include "pipe.h"

pipe_t* queue;

int queue_length;

pthread_mutex_t queue_push_mutex;
pthread_mutex_t queue_pop_mutex;
pthread_mutex_t queue_size_mutex;

int queue_init();
pipe_producer_t* queue_producer_new();
pipe_consumer_t* queue_consumer_new();
int queue_push(pipe_producer_t* producer, void* elem);
size_t queue_pop(pipe_consumer_t* consumer, void* target);
int queue_size();
int queue_push_trylock();
int queue_pop_trylock();
int queue_producer_free(pipe_producer_t* producer);
int queue_consumer_free(pipe_consumer_t* consumer);
int queue_terminate();

#endif
