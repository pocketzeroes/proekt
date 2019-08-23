#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
enum{ maxN = 1000005};

int p[maxN];

int Fib(int n, int MOD){
    int a = 1%MOD, b = 1%MOD, c;
    for(int i = 1; i <= n; ++i){
        c = (a+b)%MOD;
        a = b;
        b = c;
    }
    return c;
}
void upd(int*cnt, int n, int sign){
    while(n > 1){
        cnt[p[n]] += sign;
        n /= p[n];
    }
}
int C(int n, int k, int MOD){
    int pp[n+1]; memset(pp, 0, sizeof(pp));
    for(int i = k+1; i <= n; ++i) 
        upd(pp, i, 1);
    for(int i = 1; i <= n-k; ++i) 
        upd(pp, i, -1);
    int res = 1%MOD;
    for(int i = 1; i <= n; ++i)
        for(int x = 1; x <= pp[i]; ++x) 
            res = (1LL*res*i)%MOD;
    return res;
}
int main(){
    p[1] = 1;
    for(int i = 2; i < maxN; ++i)
        for(int j = i; j < maxN; j += i)
            if(!p[j])
                p[j] = i;
    int nTest;
    scanf("%d", &nTest);
    for(int i = 1; i <= nTest; ++i){
        int n, MOD;
        scanf("%d%d", &n, &MOD);
        int ans = Fib(n, MOD);
        if(n%2 == 0)
            ans = (ans+C(n, n/2, MOD)-((n/2+1)%MOD)+MOD)%MOD;
        printf("%d\n", ans);
    }
    return 0;
}
