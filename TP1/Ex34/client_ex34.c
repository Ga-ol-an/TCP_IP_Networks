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
gcc client_ex34.c -o client_ex34 && ./client_ex34 host_name_of_server

Examplo de host: 192.168.18.18

Exemplo:
P/ compilar e rodar:
    gcc client_ex34.c -o client_ex34 && 

Somente para rodar:
    ./client_ex34 192.168.18.18

*/
int main(int argc, char *argv[]) {
    FILE *fp;
    struct hostent *hp;
    struct sockaddr_in sin;
    char *host;
    char buf[MAX_LINE], buf_receive[MAX_LINE];
    int s;
    int len, buf_len;

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

    bzero((char *)&sin, sizeof(sin)); // which means that sin has receveid zeros here
    sin.sin_family = AF_INET;

    bcopy(&binary_address, (char *)&sin.sin_addr, sizeof(binary_address));
    sin.sin_port = htons(SERVER_PORT);
    /* active open */
    if (
        (s = socket(PF_INET, SOCK_STREAM, 0)) < 0
    ) {
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
        
        //receives from the server
        buf_len = recv(s, buf_receive, sizeof(buf), 0);
        fputs(buf_receive, stdout);
    }
}