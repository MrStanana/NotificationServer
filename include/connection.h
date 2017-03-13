#ifndef _CONNECTION_H
#define _CONNECTION_H

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

#include "config.h"

#define BACKLOG 10     // how many pending connections queue will hold

extern config_t config;
extern pthread_mutex_t mutex;

void sigchld_handler(int s);
void *get_in_addr(struct sockaddr *sa);
int create_server_socket(int port);

#endif
