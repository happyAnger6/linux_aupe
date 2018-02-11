#include "unpipc.h"

void client(int, int), server(int, int);
int main(int argc, char *argv[])
{
    int pipe1[2], pipe2[2];
    int childPid;
    
    Pipe(pipe1);
    Pipe(pipe2);
    if((childPid = Fork()) == 0){
        Close(pipe1[1]);
        Close(pipe2[0]);

        server(pipe1[0], pipe2[1]);
        exit(0);
    }

    Close(pipe1[0]);
    Close(pipe2[1]);
    client(pipe2[0], pipe1[1]);

    Waitpid(childPid, NULL, 0);
    exit(0);
}
