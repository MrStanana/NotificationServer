#include "queue.h"

int queue_init() {
    if(queue == NULL) {
        queue = pipe_new(sizeof(void*), 0);
        queue_length = 0;
        pthread_mutex_init(&queue_push_mutex, NULL);
        pthread_mutex_lock(&queue_push_mutex);
        pthread_mutex_init(&queue_pop_mutex, NULL);
        pthread_mutex_lock(&queue_pop_mutex);
        pthread_mutex_init(&queue_size_mutex, NULL);
        pthread_mutex_lock(&queue_size_mutex);
    }
    return 0;
}

pipe_producer_t* queue_producer_new() {
    return pipe_producer_new(queue);
}

pipe_consumer_t* queue_consumer_new() {
    return pipe_consumer_new(queue);
}

int queue_push(pipe_producer_t* producer, void* elem) {
    pthread_mutex_lock(&queue_push_mutex);
    pipe_push(producer, elem, 1);
    pthread_mutex_unlock(&queue_push_mutex);
    pthread_mutex_lock(&queue_size_mutex);
    queue_length++;
    pthread_mutex_unlock(&queue_size_mutex);
    return 0;
}

size_t queue_pop(pipe_consumer_t* consumer, void* target) {
    pthread_mutex_lock(&queue_pop_mutex);
    size_t elem = pipe_pop(consumer, target, 1);
    pthread_mutex_unlock(&queue_pop_mutex);
    pthread_mutex_lock(&queue_size_mutex);
    queue_length--;
    pthread_mutex_unlock(&queue_size_mutex);
    return elem;
}

int queue_size() {
    pthread_mutex_lock(&queue_size_mutex);
    return queue_length;
    pthread_mutex_unlock(&queue_size_mutex);
}

int queue_push_trylock() {
    return pthread_mutex_trylock(&queue_push_mutex);
}

int queue_pop_trylock() {
    return pthread_mutex_trylock(&queue_pop_mutex);
}

int queue_producer_free(pipe_producer_t* producer) {
    pipe_producer_free(producer);
    return 0;
}

int queue_consumer_free(pipe_consumer_t* consumer) {
    pipe_consumer_free(consumer);
    return 0;
}

int queue_terminate() {
    if(queue != NULL) {
        pipe_free(queue);
        pthread_mutex_destroy(&queue_push_mutex);
        pthread_mutex_destroy(&queue_pop_mutex);
        pthread_mutex_destroy(&queue_size_mutex);
    }
    return 0;
}
