#include <stdio.h>
#include <stdlib.h>

#include "unpipc.h"

int main(){
    int a = 10, b = 100;

    printf("a=[%d] b=[%d]\r\n",a,b);
    printf("[%s]\r\n",px_ipc_name("test"));
    
    return 0;
}
