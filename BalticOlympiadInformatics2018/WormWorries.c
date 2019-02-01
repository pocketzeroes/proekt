#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int main(){
    int n, m, k, maxq;
    scanf("%d %d %d %d", &n, &m, &k, &maxq);
    int lo = 1, hi = n+1;
    while(lo+1 < hi){
        int mi = (lo + hi) / 2;
        int r1, r2;
        printf("? %d 1 1\n", mi-1);
        scanf("%d", &r1);
        if (r1 == -1) 
            exit(0);
        printf("? %d 1 1", mi);
        scanf("%d", &r2);
        if(r2 == -1)
            exit(0);
        if(r1 >= r2) 
            hi = mi;
        else 
            lo = mi;
    }
    printf("! %d 1 1\n", lo);
    return 0;
}
