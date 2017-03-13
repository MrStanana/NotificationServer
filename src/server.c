#include "server.h"

int main(void) {
    pthread_t control_server, user_server, module_server;
    int result;

    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_lock(&mutex);
    config_init();
    queue_init();

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
    pthread_mutex_destroy(&mutex);
    queue_terminate();
    config_terminate();
    exit(EXIT_SUCCESS);
}
