
/*
 * sender.c -- multicasts "hello, world!" to a multicast group once a second
 *
 * Antony Courtney,	25/11/94
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define HELLO_PORT 23932
#define HELLO_GROUP "239.255.199.34"

int main()
{
  struct sockaddr_in addr;
  int fd /*, cnt*/;
  /* struct ip_mreq mreq; */
  
  /* create what looks like an ordinary UDP socket */
  if ((fd=socket(AF_INET,SOCK_DGRAM,0)) < 0) {
    perror("socket");
    exit(1);
  }
  
  /* set up destination address */
  memset(&addr,0,sizeof(addr));
  addr.sin_family=AF_INET;
  addr.sin_addr.s_addr=inet_addr(HELLO_GROUP);
  addr.sin_port=htons(HELLO_PORT);
  
  /* now just sendto() our destination! */
  while (1) {
    time_t tm_secs = time(NULL);
    struct tm *my_tm = localtime(&tm_secs);
    char *message = asctime(my_tm);
    if (sendto(fd, message, strlen(message)+1, 0, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
      perror("sendto");
      exit(1);
    }
    sleep(1);
  }
}

