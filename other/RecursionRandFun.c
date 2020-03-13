#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int a, b, c, maxI, minI, k;

bool check_possible(){
    for(int ii = minI; ii <= maxI; ++ii) {
        int B = k - a * ii - 1;
        if(B == 0){
            puts("possible");
            return true;
        }
        int times=0;
        for(int bb=b-1; bb>0; --bb){
            times += B / bb;
            B = B % bb;
            if(B == 0){
                if(times <= ii){
                    puts("possible");
                    return true;
                }
                break;
            }
        }
    }
    return false;
}
int ceil_div(int dividend, int divisor){
    return(dividend + divisor - 1)/divisor;
}
int main(){
    while(1){
        int rv = scanf("%d %d %d %d %d", &a, &b, &c, &maxI, &k);
        if(rv==EOF)
            break;
        minI = ceil_div(maxI, c);
        if(minI * a + 1 > k || maxI * (a + b) + 1 < k)
            puts("impossible");
        else if(!check_possible())
            puts("impossible");
    }
    return 0;
}
