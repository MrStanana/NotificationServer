#include "config.h"

//TODO: add error handling

int config_init() {
    config.control_server_port = 45201;
    config.user_server_port = 45202;
    config.module_server_port = 45203;
    char* source = config_read_file(_CONFIG_FILE);
    config_parse(source);
    free(source);
    return 0;
}

char* config_read_file(char* path) {
    char *source = NULL;
    FILE *fp = fopen(path, "r");
    if (fp != NULL) {
        if (fseek(fp, 0L, SEEK_END) == 0) {
            long bufsize = ftell(fp);
            if (bufsize == -1) { /* Error */ }
            source = malloc(sizeof(char) * (bufsize + 1));
            if (fseek(fp, 0L, SEEK_SET) != 0) { /* Error */ }
            size_t newLen = fread(source, sizeof(char), bufsize, fp);
            if ( ferror( fp ) != 0 ) {
                fputs("Error reading config file", stderr);
            } else {
                source[newLen++] = '\0';
            }
        }
        fclose(fp);
    }
    return source;
}

int config_parse(char* source) {
    cJSON* root = cJSON_Parse(source);
    cJSON* ports = cJSON_GetObjectItem(root, "ports");
    cJSON* value;
    if((value = cJSON_GetObjectItem(ports, "control_server")) != NULL) {
        config.control_server_port = value->valueint;
    }
    if((value = cJSON_GetObjectItem(ports, "user_server")) != NULL) {
        config.user_server_port = value->valueint;
    }
    if((value = cJSON_GetObjectItem(ports, "module_server")) != NULL) {
        config.module_server_port = value->valueint;
    }
    cJSON_Delete(root);
    return 0;
}

int config_terminate() {
    cJSON *root, *ports;
    root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "ports", ports = cJSON_CreateObject());
    cJSON_AddNumberToObject(ports, "control_server", config.control_server_port);
    cJSON_AddNumberToObject(ports, "user_server", config.user_server_port);
    cJSON_AddNumberToObject(ports, "module_server", config.module_server_port);
    char *rendered = cJSON_Print(root);
    cJSON_Delete(root);
    FILE *f;
    if ((f = fopen(_CONFIG_FILE, "w")) == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    fprintf(f, "%s", rendered);
    fclose(f);
    return 0;
}
