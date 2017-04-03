#include "database.h"

int database_init() {
    mysql_library_init();
}

int database_credentials() {

}

MYSQL* database_thread_new() {
    MYSQL* conn = mysql_init();
    mysql_real_connect(conn);
    return conn;
}

MYSQL* database_thread_terminate() {
    mysql_thread_end();
}

int queue_terminate() {
    mysql_library_end();
}
