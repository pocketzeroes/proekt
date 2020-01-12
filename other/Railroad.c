#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int main(){
    int X, Y;
    scanf("%d %d", &X, &Y);
    if((X*4+Y*3)%2==0)
        puts("possible");
    else
        puts("impossible");
    return 0;
}
