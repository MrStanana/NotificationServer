#ifndef _DATABASE_H
#define _DATABASE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <mysql/mysql.h>

#include "json.h"
#include "config.h"

typedef struct database_t {
    char* host;
    char* user;
    char* passwd;
    char* db;
    int port;
} database_t;

database_t database;

int database_init();
int database_credentials();
MYSQL* database_thread_new();
void database_thread_terminate();
void database_terminate();

#endif
