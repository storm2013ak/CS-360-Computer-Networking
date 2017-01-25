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

  struct hostent *hp;
  struct sockaddr_in sin;
  char *host;
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
  

  return 0;
}

