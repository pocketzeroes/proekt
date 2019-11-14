#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int main(){
    int a, b;
    scanf("%d %d", &a, &b);
    if(b == 1){
        if(a % 2 == 0)
            printf("%d\n", a / 2);
        else
            puts("0");
    }
    else{
        if(a % 2 == 0 && (a-2) % 4 == 0)
            printf("%d\n", a / 2);
        else
            puts("0");
    }
    return 0;
}
