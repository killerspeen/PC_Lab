/*
*  	Protocoale de comunicatii: 
*  	Laborator 6: UDP
*	mini-server de backup fisiere
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <sys/socket.h>

#include "helpers.h"


void usage(char*file)
{
  fprintf(stderr,"Usage: %s server_port file\n",file);
  exit(0);
}

/*
* Utilizare: ./server server_port nume_fisier
*/
int main(int argc,char**argv)
{
  int fd;
  if (argc != 3)
    usage(argv[0]);

  struct sockaddr_in my_sockaddr,from_station ;
  socklen_t adr_len = 0;
  char buf[BUFLEN];


  /*Deschidere socket*/
  int sockfd = socket(PF_INET, SOCK_DGRAM, 0);

  /*Setare struct sockaddr_in pentru a asculta pe portul respectiv */
  my_sockaddr.sin_family = AF_INET;
  my_sockaddr.sin_port = htons(atoi(argv[1]));
  my_sockaddr.sin_addr.s_addr = inet_addr("172.16.4.59");

  /* Legare proprietati de socket r*/
  bind(sockfd, (struct sockaddr *) &my_sockaddr, sizeof(my_sockaddr));

  /* Deschidere fisier pentru scriere */
  DIE((fd=open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,0644))==-1,"open file");

  /*
  * cat_timp  mai_pot_citi
  * citeste din socket
  * pune in fisier
  */
  int lg;
  char file_name[BUFLEN];

  while ((lg = recvfrom(sockfd, buf, BUFLEN, 0,
                  (struct sockaddr *) &from_station,
                  &adr_len)) > 0) {

    if (buf[0] == 1) {
      printf("%d\n", lg);
      close(fd);
      memcpy(file_name, buf + 1, lg - 1);
      file_name[lg - 1] = 0;
      puts(file_name);
      DIE((fd=open(file_name, O_WRONLY|O_CREAT|O_TRUNC, 0644))==-1,"open file");
    }
    else
      write(fd, buf + 1, lg - 1);
  }


  /*Inchidere socket*/
  close(sockfd);

  /*Inchidere fisier*/
  close(fd);

  return 0;
}
