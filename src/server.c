#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>

#include "config.h"
#include "threads.h"

config_t config;
pthread_mutex_t mutex;

int main(void) {
    pthread_t control_server, user_server, module_server;
    int result;

    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_lock(&mutex);
    config_init("config.txt");

    if((result = pthread_create(&control_server, NULL, control_thread, NULL))) {
        fprintf(stderr,"Error - pthread_create() return code: %d\n", result);
        exit(EXIT_FAILURE);
    }
    if((result = pthread_create(&user_server, NULL, user_thread, NULL))) {
        fprintf(stderr,"Error - pthread_create() return code: %d\n", result);
        exit(EXIT_FAILURE);
    }
    if((result = pthread_create(&module_server, NULL, module_thread, NULL))) {
        fprintf(stderr,"Error - pthread_create() return code: %d\n", result);
        exit(EXIT_FAILURE);
    }

    pthread_join(control_server, NULL);
    pthread_join(user_server, NULL);
    pthread_join(module_server, NULL);

    sleep(2);
    config_terminate("config.txt");
    exit(EXIT_SUCCESS);
}
