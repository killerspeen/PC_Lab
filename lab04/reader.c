#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_L 100

int main() {
  int fd_data;
  int fd_ack;

  char buf[MAX_L];

  char secv = 1;

  int test = 1;

  while(1) {
    fd_data = open("data", O_RDONLY);
    read(fd_data, buf, MAX_L);
    close(fd_data);

    if(buf[0] ==  1 - secv) {
      printf("%s\n", (buf + 1));
      secv = 1 - secv;
    }

    /* From time to time do not send ack, just to check. */
    if(test % 5) {
      fd_ack = open("ack", O_WRONLY);
      write(fd_ack, &secv, 1);
      close(fd_ack);
    }

    test ++;
  }

}
