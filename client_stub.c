/* Client code:
    active open
    connect(send, recv, close)     
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define SERVER_PORT 5432
#define MAX_LINE 256

int main(int argc, char * argv[]) {

    struct hostent *hp; // host entry
    struct sockaddr_in sin;
    char *host; // pointer to host 
    char buf[MAX_LINE];
    int s;
    int len;
    
    if (argc==2) {
        host = argv[1];
    }
    else
    {
        fprintf(stderr, "usage: simplex-talk host\n");
        exit(1);
    }
    
    /* translate name to ip addr (invoke resolver) */
    hp = gethostbyname(host); // gethostbyname only works for IPv4
    if (!hp) {
        fprintf(stderr, "simplex-talk: uknown host: %s\n", host);
        exit(1);
    }
    
    /* build address data structure */
    bzero((char *)&sin, sizeof(sin));
    sin.sin_family = AF_INET; // address family internet
    bcopy(hp->h_addr, (char *)&sin.sin_addr, hp->h_length); // bcopy - byte copy.
    sin.sin_port = htons(SERVER_PORT); // port is determined by the service 
    /* active open */
    if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket call failed");
        exit(1);
    }
    /* connect to the host */
    if (connect(s, (struct sockaddr *) &sin, sizeof(sin)) < 0)
    {
        perror("connect call failed");
        close(s);
        exit(1);
    }
    
    /* get text from user and sent to server */    
    /* main loop get and send lines of text */
    while (fgets(buf, sizeof(buf), stdin)) //fgets returns number of bytes that it read
    {
        buf[MAX_LINE - 1] = '\0';
        len = strlen(buf);
        send(s, buf, len, 0);
    }
    
  

  return 0;
}

