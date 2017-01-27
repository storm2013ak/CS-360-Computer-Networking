// to listen on the network 5432

/* Server code:
    passive open
    socket
    bind
    listen
    accept(send, recv, close)     
*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <stdlib.h>
#include <unistd.h>
#include <strings.h>

#define SERVER_PORT 5432
#define MAX_PENDING 5
#define MAX_LINE 256

int main() {
  
  
    struct sockaddr_in sin; // sin for socket in type of struct.
    char buf[MAX_LINE];
    int len; // length
    socklen_t new_len; // data structure: socklen_t
    int s, new_s; // s for socket, new_s for new socket. 

    /* need to build an address data structure */
    // need to keep up with the state information of connection 
    bzero((char *) &sin, sizeof(sin)); // bzero expects a pointer
    sin.sin_family = AF_INET; // address family internet IPv4
    sin.sin_addr.s_addr = INADDR_ANY; // listen on any interface
    sin.sin_port = htons(SERVER_PORT); // convert from host to network
    
    /* setup passive open */
    if (( s = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Socket call failed");
        exit(1);
    }
    
    if ((bind(s, (struct sockaddr *) &sin, sizeof(sin))) < 0)
    {
        perror("Bind call failed");
        exit(1);
    }
    
    listen(s, MAX_PENDING); // listen mode

    /* wait for connection, then receive and print data */
    while(1)
    {
        if (( new_s = accept(s, (struct sockaddr *) &sin, &new_len)) < 0)
        {
            perror("accept call failed");
            exit(1);
        } 
        bzero(buf, sizeof(buf));
        while ((len = recv(new_s, buf, sizeof(buf), 0)) > 0)
        {
            fputs(buf, stdout);
            close(new_s);
        }
    }

    return 0;
}
