#ifndef _DATABASE_H
#define _DATABASE_H

#include <stdio.h>
#include <stdlib.h>

#include "mysql/mysql.h"
#include "json.h"

#define _CONFIG_FILE ".config"

typedef struct database_t {
    int control_server_port;
    int user_server_port;
    int module_server_port;
} database_t;

database_t database;

int database_init();
int database_credentials();
MYSQL* database_thread_new();
MYSQL* database_thread_terminate();
int queue_terminate();

#endif
