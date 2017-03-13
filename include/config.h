#ifndef _CONFIG_H
#define _CONFIG_H

#include <stdio.h>
#include <stdlib.h>

#include "json.h"

#define _CONFIG_FILE ".config"

typedef struct config_t {
    int control_server_port;
    int user_server_port;
    int module_server_port;
} config_t;

extern config_t config;

char* config_read_file(char* path);
int config_parse(char* source);
int config_init();
int config_terminate();

#endif
