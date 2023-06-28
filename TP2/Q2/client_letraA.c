#include <stdio.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>

#define SERVER_PORT 54321
#define MAX_LINE  1000

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

    /* Main loop: measure round-trip latency for different message sizes */
    for (message_size = 1; message_size <= 1001; message_size += 100) {
        len = message_size;

        clock_t start = clock();
        for (int i = 0; i < 100000; i++) {
            generate_random_message(buf, len);

            clock_t send_start = clock();
            sendto(s, buf, len, 0, (struct sockaddr *)&sin, sizeof(sin));
            recvfrom(s, buf, sizeof(buf), 0, NULL, NULL);
            clock_t send_end = clock();

            double latency = (double)(send_end - send_start) / CLOCKS_PER_SEC;
            // Print latency for each message if needed
            // printf("Latency for %d-byte message: %.6f seconds\n", len, latency);
        }
        clock_t end = clock();

        double total_time = (double)(end - start) / CLOCKS_PER_SEC;
        double avg_latency = total_time / 100000;
        printf("Message size: %d bytes\n", message_size);
        printf("Average round-trip latency: %.6f seconds\n", avg_latency);
        printf("-----------------------------------------\n");
    }

    close(s);
    return 0;
}