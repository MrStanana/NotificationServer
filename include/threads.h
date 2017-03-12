#ifndef _THREADS_H
#define _THREADS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <pthread.h>

#include "config.h"

#define BACKLOG 10     // how many pending connections queue will hold

extern config_t config;
extern pthread_mutex_t mutex;

void sigchld_handler(int s);
void *get_in_addr(struct sockaddr *sa);
int create_server_socket(int port);
void* control_thread();
void* user_thread();
void* module_thread();
void* worker_thread(void* fd);

#endif
