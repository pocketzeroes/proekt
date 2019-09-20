#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
#define swap(a,b) do{ typeof(a) tp; tp = a; a = b; b = tp; }while(0)
typedef long long ll;
const ll mod = 1000000007ll;

int main() {
    int N, P;
    scanf("%d %d", &N, &P);
    int ed[N]; clr(ed);
    for (int i = 0; i < (P); ++i){
        int a, b;
        scanf("%d %d", &a, &b);
        --a, --b;
        if(a > b)
            swap(a, b);
        ed[b] = fmax(ed[b], a+1);
    }
    ll res   [N+1]; clr( res);
    ll sumres[N+1]; clr(sumres);
    res[0]     = 1;
    int howfar = 0;
    ll sumall  = 0;
    for (int i = 0; i < (N); ++i){
        sumall      = (sumall + res[i]) % mod;
        sumres[i+1] = sumall;
        howfar      = fmax(howfar, ed[i]);
        res[i+1]    = (sumall - sumres[howfar]) % mod;
    }
    ll r = res[N] % mod;
    if(r < 0)
       r += mod;
    printf("%lld\n", r);
    return 0;
}
