#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>

#define SERVER_PORT 54321
#define MAX_PENDING 5
#define MAX_LINE 256

int main() {
    struct sockaddr_in sin;
    char buf[MAX_LINE];
    int buf_len, addr_len;
    int s, new_s;

    /* Build address data structure */
    bzero((char *)&sin, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(SERVER_PORT);

    /* Setup passive open */
    if ((s = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("simplex-talk: socket");
        exit(1);
    }
    if ((bind(s, (struct sockaddr *)&sin, sizeof(sin))) < 0) {
        perror("simplex-talk: bind");
        exit(1);
    }

    /* Timing variables for round-trip latency */
    clock_t start, end;
    double total_time = 0;
    int test_count = 100000;

    /* Main loop: Receive and echo messages */
    while (test_count > 0) {
        addr_len = sizeof(sin);

        start = clock();
        buf_len = recvfrom(s, buf, sizeof(buf), 0, (struct sockaddr *)&sin, &addr_len);
        sendto(s, buf, buf_len, 0, (struct sockaddr *)&sin, addr_len);
        end = clock();

        total_time += (double)(end - start) / CLOCKS_PER_SEC;
        test_count--;
    }

    double avg_latency = total_time / 100000;
    printf("Round-trip latency: %.6f seconds\n", avg_latency);

    /* Calculate and print throughput for different message sizes */
    int message_size;
    for (message_size = 1; message_size <= 32; message_size++) {
        double throughput = ((double)message_size * 8) / avg_latency;
        printf("Throughput for %d KB message: %.2f bits/second\n", message_size, throughput);
    }

    close(s);
    return 0;
}