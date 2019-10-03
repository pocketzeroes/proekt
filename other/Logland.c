#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
enum{ MOD = 1000000007};

int main(){
    int K;
    scanf("%d", &K);
    ll leave = 0;
    ll cur = 1;
    ll extras = 0;
    for(int i = 0; i < K; ++i){
        ll has;
        scanf("%lld", &has);
        has += extras;
        if((has&1) && !extras)
            leave = (leave + cur) % MOD;
        extras = has / 2;
        cur = (cur * 2) % MOD;
    }
    printf("%lld\n", leave);
    return 0;
}
