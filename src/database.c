#include "database.h"

int database_init() {
    return mysql_library_init(0, NULL, NULL);
}

int database_parse(char* source) {
    cJSON* root = cJSON_Parse(source);
    cJSON* db = cJSON_GetObjectItem(root, "database");
    cJSON* value;
    if((value = cJSON_GetObjectItem(db, "host")) != NULL) {
        database.host = strdup(value->valuestring);
    }
    if((value = cJSON_GetObjectItem(db, "user")) != NULL) {
        database.user = strdup(value->valuestring);
    }
    if((value = cJSON_GetObjectItem(db, "passwd")) != NULL) {
        database.passwd = strdup(value->valuestring);
    }
    if((value = cJSON_GetObjectItem(db, "db")) != NULL) {
        database.db = strdup(value->valuestring);
    }
    if((value = cJSON_GetObjectItem(db, "port")) != NULL) {
        database.port = (int)value->valuedouble;
    }
    cJSON_Delete(root);
    return 0;
}

int database_credentials() {
    char* source = config_read_file(_PRIVATE_CONFIG_FILE);
    database_parse(source);
    free(source);
    return 0;
}

MYSQL* database_thread_new() {
    MYSQL* conn = mysql_init(NULL);
    mysql_real_connect(conn, database.host, database.user, database.passwd, database.db, database.port, NULL, 0);
    return conn;
}

void database_thread_terminate() {
    mysql_thread_end();
}

void database_terminate() {
    mysql_library_end();
}
