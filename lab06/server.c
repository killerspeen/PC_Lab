/*
*  	Protocoale de comunicatii: 
*  	Laborator 6: UDP
*	mini-server de backup fisiere
*/

#include "helpers.h"


void usage(char*file)
{
	fprintf(stderr,"Usage: %s server_port file\n",file);
	exit(0);
}

/*
*	Utilizare: ./server server_port nume_fisier
*/
int main(int argc,char**argv)
{
	if (argc!=3)
		usage(argv[0]);
	
	struct sockaddr_in my_sockaddr,from_station ;
	char buf[BUFLEN];


	/*Deschidere socket*/
	
	
	/*Setare struct sockaddr_in pentru a asculta pe portul respectiv */

	
	/* Legare proprietati de socket */

	
	
	/* Deschidere fisier pentru scriere */
	DIE((fd=open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,0644))==-1,"open file");
	
	/*
	*  cat_timp  mai_pot_citi
	*		citeste din socket
	*		pune in fisier
	*/


	/*Inchidere socket*/	

	
	/*Inchidere fisier*/

	return 0;
}
