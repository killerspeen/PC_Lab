#include <stdio.h>
#include <unistd.h>

#include "alarm.h"

/*
* Cat ar trebui sa dureze executia programului? 
* Cat dureaza in realitatea executia ? De ce?
*/
int main()
{
	const int *was_timeout;
	init_alarm();
	
	was_timeout=set_alarm(2);
	sleep(1);
	cancel_alarm();
	printf("was_timeout=%d\n", *was_timeout);

	was_timeout=set_alarm(1);
	sleep(10);
	cancel_alarm();
	printf("was_timeout=%d\n", *was_timeout);

	

	cleanup_alarm();	
	return 0;	
}
