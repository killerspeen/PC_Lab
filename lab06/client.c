/*
*  	Protocoale de comunicatii: 
*  	Laborator 6: UDP
*	client mini-server de backup fisiere
*/

/*

	myaddr.famil7 - afinet
	port = htons
	sinaddr.s_addr = inet_addr(IP)
	inet = htonl?


*/

#include "helpers.h"

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


void usage(char*file)
{
	fprintf(stderr,"Usage: %s ip_server port_server file\n",file);
	exit(0);
}

/*
*	Utilizare: ./client ip_server port_server nume_fisier_trimis
*/
int main(int argc,char**argv)
{
	if (argc!=4)
		usage(argv[0]);
	
	int fd;
	struct sockaddr_in to_station;
	char buf[BUFLEN];

	int sfd,err,bytes_read,i=0;
	char packetype=1;
	char filename[20];
	strcpy(filename, argv[3]);


	/*Deschidere socket*/
	sfd = socket(PF_INET, SOCK_DGRAM, 0);
	DIE( sfd == -1, "open socket" );

	
	/* Deschidere fisier pentru citire */
	DIE((fd=open(argv[3],O_RDONLY))==-1,"open file");
	
	/*Setare struct sockaddr_in pentru a specifica unde trimit datele*/
	to_station.sin_family = AF_INET;
	to_station.sin_port = htons(atoi(argv[2]));
	to_station.sin_addr.s_addr = inet_addr(argv[1]);
	//to_station.sin_addr.s_addr = hotnl(to_station.sin_addr.s_addr);
	
	
	/*
	*  cat_timp  mai_pot_citi
	*		citeste din fisier
	*		trimite pe socket
	*/
	bytes_read = 1+strlen(filename)+1;
	memcpy(buf,&packetype,1);
	memcpy(buf+1,filename,strlen(filename)+1);

	while(bytes_read > 1){

		err = sendto(sfd, buf, bytes_read, 0,  (struct sockaddr *)&to_station, sizeof(struct sockaddr));
		DIE(err==-1, "sending");

		if(i<5)
			printf("\nSent %dth packet of len:%d /w type:%d",i, bytes_read, buf[0]);
		if(i==0)
			printf("\nbuf[0]:%d , buf+1:%s", buf[0], buf+1);
		i++;

		packetype = 0;
		memcpy(buf,&packetype,1);
		bytes_read = read(fd,buf+1,BUFLEN-1);
		bytes_read += 1;
		
	}
	err = sendto(sfd, buf, bytes_read, 0,  (struct sockaddr *)&to_station, sizeof(struct sockaddr));
	DIE(err==-1, "sending");


	/*Inchidere socket*/
	close(sfd);
	
	/*Inchidere fisier*/
	close(fd);

	return 0;
}
