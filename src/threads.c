#include "threads.h"

void sigchld_handler(int s) {
    // waitpid() might overwrite errno, so we save and restore it:
    int saved_errno = errno;
    while(waitpid(-1, NULL, WNOHANG) > 0);
    errno = saved_errno;
}

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa) {
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int create_server_socket(int port) {
    int sockfd, result, yes = 1;
    struct addrinfo hints, *servinfo, *p;
    struct sigaction sa;
    char port_s[5];
    sprintf(port_s, "%d", port);

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // use my IP

    if ((result = getaddrinfo(NULL, port_s, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(result));
        return 1;
    }

    // loop through all the results and bind to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("server: socket");
            continue;
        }
        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
            perror("setsockopt");
            exit(1);
        }
        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("server: bind");
            continue;
        }
        break;
    }

    freeaddrinfo(servinfo); // all done with this structure

    if (p == NULL)  {
        fprintf(stderr, "server: failed to bind\n");
        exit(1);
    }

    if (listen(sockfd, BACKLOG) == -1) {
        perror("listen");
        exit(1);
    }

    sa.sa_handler = sigchld_handler; // reap all dead processes
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    return sockfd;
}

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
        printf("server: got connection from %s\n", s);
        if((result = pthread_create(&conn, NULL, worker_thread, (void*)&new_fd))) {
            fprintf(stderr,"Error - pthread_create() return code: %d\n", result);
        }
    }
    close(sockfd);
    return 0;
}

void* user_thread() {
    int sockfd, new_fd, result;
    struct sockaddr_storage their_addr;
    socklen_t sin_size;
    char s[INET6_ADDRSTRLEN];
    pthread_t conn;

    sockfd = create_server_socket(config.user_server_port);
    printf("user server: waiting for connections...\n");
    while(pthread_mutex_trylock(&mutex)) {
        sin_size = sizeof their_addr;
        new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
        if (new_fd == -1) {
            perror("accept");
            continue;
        }
        inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *)&their_addr), s, sizeof s);
        printf("server: got connection from %s\n", s);
        if((result = pthread_create(&conn, NULL, worker_thread, (void*)&new_fd))) {
            fprintf(stderr,"Error - pthread_create() return code: %d\n", result);
        }
    }
    close(sockfd);
    return 0;
}

void* module_thread() {
    int sockfd, new_fd, result;
    struct sockaddr_storage their_addr;
    socklen_t sin_size;
    char s[INET6_ADDRSTRLEN];
    pthread_t conn;

    sockfd = create_server_socket(config.module_server_port);
    printf("module server: waiting for connections...\n");
    while(pthread_mutex_trylock(&mutex)) {
        sin_size = sizeof their_addr;
        new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
        if (new_fd == -1) {
            perror("accept");
            continue;
        }
        inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *)&their_addr), s, sizeof s);
        printf("server: got connection from %s\n", s);
        if((result = pthread_create(&conn, NULL, worker_thread, (void*)&new_fd))) {
            fprintf(stderr,"Error - pthread_create() return code: %d\n", result);
        }
    }
    close(sockfd);
    return 0;
}

void* worker_thread(void* fd) {
    int sockfd = *(int*)fd;
    if (send(sockfd, "Hello, world!", 13, 0) == -1) {
        perror("send");
    }
    close(sockfd);
    return 0;
}
