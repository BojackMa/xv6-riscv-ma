#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int p[2],q[2];


int
main(int argc, char *argv[])
{
  pipe(p);
  pipe(q);
  char buf1[1024], buf2[1024];
  
  if(fork() == 0) {
    read(p[0], buf2, 5); 
    close(p[0]);
    fprintf(2, "%d: received ping\n",getpid());
    write(q[1], "pong\n", 5);
    close(q[1]);
   } else {
    write(p[1], "ping\n", 5);
    close(p[1]);
    read(q[0], buf1, 5);
    close(q[0]);
    fprintf(2, "%d: received pong\n",getpid());
   }

  exit(0);
}