#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
enum{NR = 1000000000};

int main(){
    int n, x, maxim=0, minim=NR+1;
    scanf("%d", &n);
    for(int i=1;i<=n;i++){
        scanf("%d", &x);
        x = fmax(x,NR-x);
        maxim = fmax(maxim,x);
        minim = fmin(minim,x);
    }
    printf("%d\n", maxim - minim);
    return 0;
}
