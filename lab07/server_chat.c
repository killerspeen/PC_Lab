
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

  struct sockaddr_in my_addr, cli_addr1, cli_addr2;

  my_addr.sin_family = AF_INET;
  my_addr.sin_port = htons(45555);
  my_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  if (bind(sockfd, (struct sockaddr *) &my_addr, sizeof(my_addr)) == -1) {
    perror("Unable to bind.");
    exit(1);
  }

  if (listen(sockfd, 2) == -1) {
    perror("Unable to listen");
    exit(1);
  }

  int lg1 = 0, lg2 = 0;
  int fd1 =  accept(sockfd, (struct sockaddr *) &cli_addr1, &lg1);
  int fd2 =  accept(sockfd, (struct sockaddr *) &cli_addr2, &lg2);


  char buf[1000];
  int ok;

  strcpy(buf, "WAIT");
  send(fd1, buf, strlen(buf) + 1, 0);

  while (1) {

    ok = recv(fd1, buf, 1000, 0);
    if (ok == 0)
      break;

    send(fd2, buf, strlen(buf) + 1, 0);

    ok = recv(fd2, buf, 1000, 0);
    if (ok == 0)
      break;

    send(fd1, buf, strlen(buf) + 1, 0);
  }

  close(fd1);
  close(fd2);
  close(sockfd);

  return 0;
}


