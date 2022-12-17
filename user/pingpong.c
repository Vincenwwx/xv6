#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    int p[2];
    close(0);
    pipe(p);
    dup(p[0]);

    if(fork() == 0) { // child
        char b;
        read(0, &b, 1);
        close(0);
        int pid = getpid();
        fprintf(1, "%d: received ping\n", pid);
        write(p[1], &b, 1);
        close(p[1]);
    }
    else {  // parent
        char b = 'h';
        write(p[1], &b, 1);
        close(p[1]);
        read(0, &b, 1);
        int pid = getpid();
        fprintf(1, "%d: received pong\n", pid);
    }

    exit(0);
}