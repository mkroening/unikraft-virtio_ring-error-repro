#include <arpa/inet.h>   // for htons
#include <assert.h>      // for assert
#include <netinet/in.h>  // for sockaddr_in, INADDR_ANY
#include <stdio.h>       // for printf, ssize_t
#include <stdlib.h>      // for free, malloc
#include <string.h>      // for memset
#include <sys/socket.h>  // for accept, bind, listen, socket, AF_INET, SOCK_...
#include <unistd.h>      // for close, write, sleep

#define BUF_LEN (128 * 1024 * 1024)

int main(void) {
    printf("Starting to listen!\n");
    int serverFd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server = {.sin_family = AF_INET,
                                 .sin_addr = {.s_addr = INADDR_ANY},
                                 .sin_port = htons(3333)};
    bind(serverFd, (struct sockaddr *)&server, sizeof(server));
    listen(serverFd, 10);

    while (1) {
        printf("Waiting for connections!\n");
        struct sockaddr_in client;
        socklen_t len = sizeof(client);
        int clientFd = accept(serverFd, (struct sockaddr *)&client, &len);

        char *buf = malloc(BUF_LEN);
        memset(buf, 0, BUF_LEN);

        printf("Writing!\n");
        ssize_t first_half = write(clientFd, buf, BUF_LEN / 2);
        assert(first_half == BUF_LEN / 2);

        printf("Half-time break!\n");
        sleep(1);
        printf("Break over!\n");

        ssize_t second_half = write(clientFd, buf + BUF_LEN / 2, BUF_LEN / 2);
        assert(second_half == BUF_LEN / 2);
        printf("Written everything!\n");

        free(buf);

        close(clientFd);
        printf("Client served!\n");
    }

    close(serverFd);
}
