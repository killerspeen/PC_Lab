#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

#define BUFLEN 256

void error(char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, n, i;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[BUFLEN];
    if (argc < 3) {
       fprintf(stderr,"Usage %s server_address server_port\n", argv[0]);
       exit(0);
    }

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[2]));
    inet_aton(argv[1], &serv_addr.sin_addr);


    if (connect(sockfd,(struct sockaddr*) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");    

    fd_set read_fs, temp_fs;
    FD_SET(sockfd, &read_fs);
    FD_SET(0, &read_fs);

    while(1){

        temp_fs = read_fs;

        select(sockfd + 1, &temp_fs, NULL, NULL, NULL);

        memset(buffer, 0 , BUFLEN);

        for (i = 0; i <= sockfd; i ++) {
          if (FD_ISSET(i, &temp_fs)) {
            if (i == 0) {
              //citesc de la tastatura
              memset(buffer, 0 , BUFLEN);
              fgets(buffer, BUFLEN-1, stdin);

              //trimit mesaj la server
              n = send(sockfd,buffer,strlen(buffer), 0);

              if (n < 0)
                       error("ERROR writing to socket");
            }
            else {
              n = recv(i, buffer, sizeof(buffer), 0);
              if (n > 0) {
                printf("\t");
                puts(buffer);
              }
            }
          }
        }



    }
    return 0;
}


