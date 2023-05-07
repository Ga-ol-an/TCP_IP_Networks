#include <stdio.h>
int main()
{
   int socket(int domain, int type, int protocol);

   // to a server:
   int bind(int socket, struct sockaddr *address, int addr_len);
   int listen(int socket, int backlog);
   int accept(int socket, struct sockaddr *address, int *addr_len);

   // to a client:
   int connect(int socket, struct sockaddr *address, int addr_len);

   //Once a connection is established, the application processes invoke the
   //following two operations to send and receive data:
   int send(int socket, char *message, int msg_len, int flags);
   int recv(int socket, char *buffer, int buf_len, int flags);
}
