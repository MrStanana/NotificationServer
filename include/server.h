#ifndef _SERVER_H
#define _SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>

#include "config.h"
#include "database.h"
#include "connection.h"
#include "control.h"
#include "user.h"
#include "module.h"

config_t config;
pthread_mutex_t mutex;

#endif
