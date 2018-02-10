#include <stdio.h>
#include <stdlib.h>

#include "swap.h"

int main(){
    int a = 10, b = 100;
    swap(&a, &b);
    printf("a=[%d] b=[%d]\r\n",a,b);
    return 0;
}
