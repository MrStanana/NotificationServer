#include "control.h"

void* control_thread() {
    int sockfd, new_fd, result;
    struct sockaddr_storage their_addr;
    socklen_t sin_size;
    char s[INET6_ADDRSTRLEN];
    pthread_t conn;

    sockfd = create_server_socket(config.control_server_port);
    printf("control server: waiting for connections...\n");
    while(pthread_mutex_trylock(&mutex)) {
        sin_size = sizeof their_addr;
        new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
        if (new_fd == -1) {
            perror("accept");
            continue;
        }
        inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *)&their_addr), s, sizeof s);
        printf("control server: got connection from %s\n", s);
        if((result = pthread_create(&conn, NULL, control_worker_thread, (void*)&new_fd))) {
            fprintf(stderr,"Error - pthread_create() return code: %d\n", result);
        }
    }
    close(sockfd);
    return 0;
}

void* control_worker_thread(void* fd) {
    int sockfd = *(int*)fd;
    if (send(sockfd, "Hello, world!", 13, 0) == -1) {
        perror("send");
    }
    close(sockfd);
    return 0;
}
