#include <stdio.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>

#define SERVER_PORT 54321
#define MAX_LINE 256

void generate_random_message(char *buf, int len) {
    static const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int i;
    for (i = 0; i < len - 1; i++) {
        buf[i] = charset[rand() % (sizeof(charset) - 1)];
    }
    buf[len - 1] = '\0';
}

int main(int argc, char *argv[]) {
    FILE *fp;
    struct hostent *hp;
    struct sockaddr_in sin;
    char *host;
    char buf[MAX_LINE];
    int s;
    int len;
    int message_size;

    if (argc == 2) {
        host = argv[1];
    } else {
        fprintf(stderr, "usage: simplex-talk host\n");
        exit(1);
    }

    /* translate host ASCII notation to Binary */
    in_addr_t binary_address = inet_addr(host);
    if (!binary_address) {
        fprintf(stderr, "simplex-talk: unknown host: %s\n", host);
        exit(1);
    }

    /* build address data structure */
    bzero((char *)&sin, sizeof(sin));
    sin.sin_family = AF_INET;
    bcopy(&binary_address, (char *)&sin.sin_addr, sizeof(binary_address));
    sin.sin_port = htons(SERVER_PORT);

    /* active open */
    if ((s = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("simplex-talk: socket");
        exit(1);
    }

    srand(time(NULL)); // Initialize random seed

    /* Main loop: measure throughput for different message sizes */
    for (message_size = 1; message_size <= 32; message_size++) {
        len = message_size * 1024; // Convert kilobytes to bytes

        clock_t start = clock();
        for (int i = 0; i < 100000; i++) {
            generate_random_message(buf, len);
            sendto(s, buf, len, 0, (struct sockaddr *)&sin, sizeof(sin));
            recvfrom(s, buf, sizeof(buf), 0, NULL, NULL);
        }
        clock_t end = clock();

        double total_time = (double)(end - start) / CLOCKS_PER_SEC;
        double avg_throughput = ((double)message_size * 8) / (total_time / 100000);
        printf("Average throughput for %d KB message: %.2f bits/second\n", message_size, avg_throughput);
    }

    close(s);
    return 0;
}