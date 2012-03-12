#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "alarm/alarm.h"

#define MAX_L 100

char * phrase = "Stuff this in your pipe and smoke it";

int main() {
  int fd_data;
  int fd_ack;

  int tle = 3, *p, secv = 0;
  char ack;
  char buf[MAX_L];

  init_alarm();

  fgets(buf + 1, MAX_L - 1, stdin);

  while(1) {
    buf[0] = secv;

    fd_data = open("data", O_WRONLY);
    write(fd_data, buf, strlen(buf + 1) + 2);
    close(fd_data);

    p = set_alarm(tle);
    fd_ack = open("ack", O_RDONLY);
    read(fd_ack, &ack, 1);
    close(fd_ack);
    cancel_alarm();

    if(*p == 0 && ack == secv) {
      printf("\tRecived ACK. Enter new data\n");
      fgets(buf + 1, MAX_L - 1, stdin);
      secv = 1 - secv;
    }
    else
      printf("\tNo or wrong ACK recived, resending\n");

  }

  cleanup_alarm();

  return 0;
}
