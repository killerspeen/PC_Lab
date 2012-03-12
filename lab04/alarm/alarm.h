#ifndef _ALARM_H
#define _ALARM_H

/**
 ** Resets the timer. 
 ** It makes *P = 0, where P = pointer returned by set_alarm P
 ** You must call this function after each set_alarm function
 **/
extern void cancel_alarm();


/**
 ** Sets the timer. 
 ** timeout => number of seconds after the timer expires
 ** @return => pointer P to a variable that tells if it was a timeout
 ** 		*P = 0 if delta_time<timeout
 ** 		*P = 1 if delta_time>=timeout
 ** where delta_time is the time between set_alarm and checking *P
 **/
extern const int * set_alarm(unsigned int timeout);

/**
 ** Initializes the timer. 
 ** You must call this function at the beginning of your program
 **/
extern int init_alarm();

/**
 ** Restores the resources of the timer.
 ** You must call this function at the end of your programn
 **/
extern void cleanup_alarm();


#endif //_ALARM_H
