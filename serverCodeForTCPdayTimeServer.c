/*-----------------------------------------------------------------------
Name:	Abdullah Karaman
Class:	CS 360 Computer Networking
Assignment: Assignment #1
Resources: http://www.cplusplus.com/reference/ctime/strftime/ for strftime
Description: This is the server code for TCP Day Time server
-------------------------------------------------------------------------*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <time.h> // to use time_t and tm 

#define SERVER_PORT 5401
#define MAX_PENDING 5
#define MAX_LINE 256

/* function to handle errors and print messages */ 
void handleError(const char *msg)
{
	printf(msg);
	exit(1);
}

int main() {
  
	struct sockaddr_in sin; // sin for socket in type of struct.
    char buf[MAX_LINE];
    int len; // length
    socklen_t new_len; // data structure: socklen_t
    int s, new_s; // s for socket, new_s for new socket.
	time_t currentTime;
	struct tm *timeinfo;

    /* need to build an address data structure */
    // need to keep up with the state information of connection 
    bzero((char *) &sin, sizeof(sin)); // bzero expects a pointer
    sin.sin_family = AF_INET; // address family internet IPv4
    sin.sin_addr.s_addr = INADDR_ANY; // listen on any interface
    sin.sin_port = htons(SERVER_PORT); // convert from host to network
    
    /* setup passive open */
    if (( s = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    {
		handleError("Socket call failed");
    }
    
    if ((bind(s, (struct sockaddr *) &sin, sizeof(sin))) < 0)
    {
		handleError("Bind call failed");
    }
    
    listen(s, MAX_PENDING); // listen mode

    /* wait for connection, then send the date to the client */
    while(1)
    {
        if (( new_s = accept(s, (struct sockaddr *) &sin, &new_len)) < 0)
        {
			handleError("Accept call failed");
        } 
        bzero(buf, sizeof(buf));		
		time(&currentTime);
		timeinfo = localtime(&currentTime);
		
		// strftime is the function to format the time
		strftime(buf,sizeof(buf), "%A, %B %d, %Y %T-%Z\n", timeinfo);
		send(new_s, buf, sizeof(buf),0);

		close(new_s);
    }

    return 0;
}
