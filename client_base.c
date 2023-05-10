#include <stdio.h>
// #include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h> // to use inet_addr
#include <netinet/in.h>
#include <netdb.h>

#define SERVER_PORT 54321
#define MAX_LINE 256

/*
Coloque o seu ip ao rodar esse comando, da seguinte forma:
gcc client_base.c -o client_base && ./client_base host_name_of_server

Examplo de host: 192.168.18.18

Exemplo:
P/ compilar e rodar:
    gcc client_base.c -o client_base && 

Somente para rodar:
    ./client_base 192.168.18.18

*/
int main(int argc, char *argv[]) {
    FILE *fp;
    struct hostent *hp;
    struct sockaddr_in sin;
    char *host;
    char buf[MAX_LINE];
    int s;
    int len;

    len = sizeof(sin);

    in_addr_t binary_address;
    if (argc == 2) {
        host = argv[1];
    } else {
        fprintf(stderr, "usage: simplex-talk host\n");
        exit(1);
    }

    /* translate host ASCII notation to Binary */
    //printf("%s", host);
    binary_address = inet_addr(host);
    //printf("%u", binary_address);
    if (!binary_address) {
        fprintf(stderr, "simplex-talk: unknown host: %s\n", host);
        exit(1);
    }

    /* build address data structure */
    //  Explanation: zero(void *s, size_t n) - The bzero() function shall place n zero-valued bytes in the area pointed to by s.
    bzero((char *)&sin, sizeof(sin)); // which means that sin has receveid zeros here
    sin.sin_family = AF_INET;
    // Explanation: void bcopy(const void *src, void *dest, size_t n); - The bcopy() function copies n bytes from src to dest.  The result is correct, even when both areas overlap.
    bcopy(&binary_address, (char *)&sin.sin_addr, sizeof(binary_address));
    sin.sin_port = htons(SERVER_PORT);
    /* active open */
    if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        perror("simplex-talk: socket");
        exit(1);
    }
    if (connect(s, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
        perror("simplex-talk: connect");
        close(s);
        exit(1);
    }
    /* main loop: get and send lines of text */
    while (fgets(buf, sizeof(buf), stdin)) {
        buf[MAX_LINE - 1] = '\0';
        len = strlen(buf) + 1;
        send(s, buf, len, 0);
    }
}