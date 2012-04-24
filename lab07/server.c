
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

  struct sockaddr_in my_addr, cli_addr;

  my_addr.sin_family = AF_INET;
  my_addr.sin_port = htons(45555);
  my_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  if (bind(sockfd, (struct sockaddr *) &my_addr, sizeof(my_addr)) == -1) {
    perror("Unable to bind.");
    exit(1);
  }

  if (listen(sockfd, 1) == -1) {
    perror("Unable to listen");
    exit(1);
  }

  int lg = 0;
  int fd =  accept(sockfd, (struct sockaddr *) &cli_addr, &lg);

  char buf[1000];

  while (recv(fd, buf, 1000, 0)) {
    printf("%s", buf);
  }


  close(fd);
  close(sockfd);

  return 0;
}


