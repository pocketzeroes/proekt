#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
int main(){
    ll T, N, M, K, i, j, k, count=0, a, b, c, x, y, z;
    scanf("%lld", &N);
    while(N!=0){
        y=0;
        z=N;
        while(z){
            y+=(z%10);
            z/=10;
        }
        N=N-y;
        count++;
    }
    printf("%lld\n", 1+count);
    return 0;
}
