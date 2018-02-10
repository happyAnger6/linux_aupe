#include "unpipc.h"

int main(int argc, char *argv[])
{
    struct stat stStat;
    if(argc != 2){
        err_quit("usage: ftok <pathname>");
    }

    Stat(argv[1], &stStat);
    printf("st_dev: %lx, st_ino: %lx, key: %x\n",
        stStat.st_dev, stStat.st_ino, Ftok(argv[1], 0x57));
    
    exit(0);
}
