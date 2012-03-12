#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

char * phrase = "Stuff this in your pipe and smoke it";

int main () {
  int fd1;

  fd1 = open ( "mypipe", O_WRONLY );
  write (fd1, phrase, strlen ( phrase)+1 );
  close (fd1);
}
