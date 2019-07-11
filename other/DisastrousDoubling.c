#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;

const ll MOD = 1e9+7;

int main(){
    ll b = 1LL, bm = 1LL;
    int n;
    scanf("%d", &n);
    while(n--){
        ll bi;
        scanf("%lld", &bi);
        bm = (((bm * 2LL - bi) % MOD) + MOD) % MOD;
        if(b >= 0LL){
            b *= 2LL;
            if(b > (1LL << 61))
                b = -1LL;
        }
        if(b >= 0LL){
            b -= bi;
            if(b < 0LL){
                puts("error");
                return 0;
            }
        }
    }
    printf("%lld\n", bm);
    return 0;
}
