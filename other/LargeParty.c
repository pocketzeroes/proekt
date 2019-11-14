#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
typedef long long ll;
const ll mod = 100000007;

ll accumulate(ll*arr, int sz){
  ll sum=0;
  for(int i=0; i<sz; i++)
    sum += arr[i];
  return sum;
}


ll Pow(ll a, int b) {
    if (b == 0)
        return 1;
    ll e = Pow(a, b / 2);
    e = (e * e) % mod;
    if (b % 2)
        e *= a;
    return e % mod;
}
ll inv(ll a){
    return Pow(a, mod - 2);
}
int main(){
    int t;
    scanf("%d", &t);
    for (int cases = 0; cases < t; cases++) {
        int n, k;
        scanf("%d %d", &n, &k);
        if (k > n)
            k = n;
        ll p[n+5][k+5];
        memset(p, 0, sizeof(p));
        p[1][0] = 1;
        for (int i=2; i<=n; i++) {
            p[i][0] = p[i-1][k];
            for(int j=0; j<k; j++){
                p[i][j+1] = p[i-1][j];
                p[i][0] += p[i-1][j];
            }
            p[i][0] %= mod;
        }
        for (int i=2; i<=n; i++)
            for (int j=1; j<=k; j++)
                p[i][j] = (p[i][j] * (j + 1)) % mod;
        ll r[n+1]; clr(r);
        for(int i=1; i<=n; i++)
            r[i] = accumulate(p[i], k+1) % mod;
        ll total = 0;
        for(int i=1; i<=n; i++){
            if (n%i == 0) {
                for (int j=2*i; j<=n; j+=i)
                    r[j] = (r[j] - r[i] + mod) % mod;
                total = (total + r[i] * inv(i)) % mod;
            }
        }
        if (n <= k)
            total++;
        printf("%lld\n", total % mod);
    }
    return 0;
}
