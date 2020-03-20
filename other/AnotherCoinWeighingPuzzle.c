#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
enum{mod = 998244353};
enum{MAXN = 1000005 };

int m, n;
int low[MAXN],
    moe[MAXN];

ll ipow(int x, int p){
    ll ret = 1,
       piv = x;
    for(int i=p; i; i>>=1){
        if(i & 1)
            ret = ret * piv % mod;
        piv = piv * piv % mod;
    }
    return ret;
}
int main(){
    scanf("%d %d", &m, &n);
    for(int i=2; i<=n; i++){
        for(int j=i; j<=n; j+=i){
            if(!low[j])
                low[j] = i;
        }
    }
    moe[1] = 1;
    for(int i=2; i<=n; i++){
        if(low[i] == i)
           moe[i] = -1;
        else{
            if(low[i / low[i]] == low[i])
                moe[i] = 0;
            else
                moe[i] = -moe[i / low[i]];
        }
    }
    ll ret = 1;
    for(int i=1; i<=n; i++){
        ll foo = ipow(2 * (n / i) + 1, m) - 1;
        ret += (mod + moe[i]) * foo;
        ret %= mod;
    }
    printf("%lld\n", ret);
    return 0;
}
