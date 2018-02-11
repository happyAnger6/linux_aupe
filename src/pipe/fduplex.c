#include "unpipc.h"

int main(int argc, char *argv[])
{
    int fd[2], n;
    char c;
    pid_t childPid;

    fd_pipe(fd);
    if((childPid = Fork()) == 0){
        sleep(3);
        if((n = Read(fd[0], &c, 1)) != 1){
            err_quit("child: read returned:%d", n);
        }
        printf("child read %c\n", c);
        Write(fd[0], "c", 1);
        exit(0);
    }

    Write(fd[1], "p", 1);
    if((n = Read(fd[1], &c, 1)) != 1){
        err_quit("father: read returned:%d", n);
    }
    printf("father read %c\n", c);
    exit(0);
}
