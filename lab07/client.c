
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main()
{
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in serv_addr;

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(45555);
  serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  if(connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) == -1){
    perror ("Unable to connect");
    exit(1);
  }


  char buf[1000];

  while (fgets(buf, 1000, stdin)) {
    if (strcmp(buf, "\n") == 0)
      break;
    send(sockfd, buf, strlen(buf) + 1, 0);
  }

  close(sockfd);

  return 0;
}
