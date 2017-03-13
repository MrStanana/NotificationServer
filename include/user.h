#ifndef _USER_H
#define _USER_H

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
#include <pthread.h>

#include "config.h"
#include "connection.h"

#define BACKLOG 10     // how many pending connections queue will hold

extern config_t config;
extern pthread_mutex_t mutex;

void* user_thread();
void* user_worker_thread(void* fd);

#endif
