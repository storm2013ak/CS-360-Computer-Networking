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

  struct sockaddr_in sin;
  char buf[MAX_LINE];
  int len;
  socklen_t new_len;
  int s, new_s;
  

  return 0;
}

