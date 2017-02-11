/*-----------------------------------------------------------------------
Name:	Abdullah Karaman
Class:	CS 360 Computer Networking
Assignment: Assignment #1
Description: This is the client code for TCP Day Time server
-------------------------------------------------------------------------*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define SERVER_PORT 5401
#define MAX_LINE 256

/* function to handle errors and print messages */ 
void handleError(const char *msg)
{
	printf(msg);
	exit(1);
}

int main(int argc, char * argv[]) {

    struct hostent *hp; // host entry
    struct sockaddr_in sin;
    char *host; // pointer to host 
    char buf[MAX_LINE];
    int s; // socket
    int len; // length
	char msg[31] = "Sending something to the server";

	// check for 2 arguments
    if (argc==2) 
	{
        host = argv[1];
    }
    else
    {
        fprintf(stderr, "usage: simplex-talk host\n");
        exit(1);
    }
    
    /* translate name to ip addr (invoke resolver) */
    hp = gethostbyname(host); // gethostbyname only works for IPv4
    if (!hp) 
	{
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
		handleError("Socket call failed");
    }
	
    /* connect to the host */
    if (connect(s, (struct sockaddr *) &sin, sizeof(sin)) < 0)
    {
		handleError("Connect call failed");
    }
	
	send(s, msg, sizeof(msg),0); // send message to check if server is going to ignore it
	
	// receive the date sent by the server 
	while((len = recv(s, buf, sizeof(buf)-1,0)) > 0)
	{
		buf[len] = '\0';
		if(fputs(buf,stdout) == EOF)
		{
			handleError("Error in fputs");
		}
	}
	
	close(s);
  
	return 0;
}

