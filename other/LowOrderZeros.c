#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{LIM = 1000000};

int main(){
    int f[LIM+1];
    int n2[LIM+1];
    int i, j;
    f [0] = 1;
    f [1] = 1;
    f [2] = 1;
    n2[0] = 0;
    n2[1] = 0;
    n2[2] = 1;
    for(i = 3; i <= LIM; ++i){
        n2[i] = n2[i-1];
        j = i;
        while(j % 2 == 0){
            j /= 2;
            ++n2[i];
        }
        while(j % 5 == 0){
            j /= 5;
            --n2[i];
        }
        f[i] = (f[i-1] * (j%10))%10;
    }
    int n;
    while(1){
        scanf("%d", &n);
        if(n == 0)
            return 0;
        int ans = f[n];
        for(i = 0; i < n2[n]; ++i)
            ans = (ans*2) % 10;
        printf("%d\n", ans);

    }
    return 0;
}
