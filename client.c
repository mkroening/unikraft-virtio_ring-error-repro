#include <arpa/inet.h>   // for inet_addr, htons
#include <netinet/in.h>  // for sockaddr_in
#include <stdio.h>       // for printf, ssize_t
#include <stdlib.h>      // for free, malloc
#include <sys/socket.h>  // for connect, socket, AF_INET, SOCK_STREAM
#include <unistd.h>      // for close, read

#define BUF_LEN (128 * 1024 * 1024)

int main(void) {
    printf("Connecting!\n");
    int serverFd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server = {.sin_family = AF_INET,
                                 .sin_addr = {.s_addr = inet_addr("10.0.5.3")},
                                 .sin_port = htons(3333)};
    connect(serverFd, (struct sockaddr *)&server, sizeof(server));

    printf("Reading!\n");
    char *buf = malloc(BUF_LEN);
    ssize_t s = 0;
    while (s < BUF_LEN) {
        s += read(serverFd, buf, BUF_LEN - s);
    }
    free(buf);

    close(serverFd);
    printf("Client served!\n");
}
