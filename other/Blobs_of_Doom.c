#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
void fill(ll*arr, int sz, ll val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}

ll k, n;
ll*dp;
ll*primes; int primesSz;
enum{ ITER = 50   };
enum{ M = 23000000};
bool prime[M];

ll power(ll x, ll y, ll p){
    ll res = 1;
    x = x % p;
    while (y > 0){
        if (y & 1)
            res = (res*x) % p;
        y = y>>1;
        x = (x*x) % p;
    }
    return res;
}
bool miillerTest(ll d, ll n){
    ll a = 2 + rand() % (n - 4);
    ll x = power(a, d, n);
    if (x == 1  || x == n-1)
       return true;
    while (d != n-1){
        x = (x * x) % n;
        d *= 2;
        if (x == 1)
            return false;
        if (x == n-1)
            return true;
    }
    return false;
}
bool isPrime(ll n, ll k){
    if (n <= 1 || n == 4)
        return false;
    if (n <= 3)
        return true;
    ll d = n - 1;
    while (d % 2 == 0)
        d /= 2;
    for (ll i = 0; i < k; i++)
        if (!miillerTest(d, n))
            return false;
    return true;
}
ll getprime(ll n){
    int ct = 0;
    ll temp = n;
    ll fac;
    for(int z=0;z<primesSz;z++){ll i = primes[z];
        if(i*i*i > n)
            break;
        while(n % i == 0) {
            fac = i;
            n /= i;
            ct++;
        }
        if(ct > 2)
            return ct;
    }
    if(ct == 0) {
        if(isPrime(n, ITER))
            return 1;
        else
            return 2;
    }
    if(ct == 1) {
        if(isPrime(temp/fac, ITER))
            return 2;
        return 3;
    }
    if(ct == 2) {
        if(n == 1)
            return 2;
        return 3;
    }
    return ct;
}
int main(){
    primes = calloc(2000000, sizeof(ll));
    for(int i = 2; i < M; ++i)
        prime[i] = true;
    for(int i = 2; i*i < M; ++i){
        if(prime[i]) {
            for(int j = i*i; j < M; j += i)
                prime[j] = false;
        }
    }
    for(int i=2; i<M; ++i){
        if(prime[i]){
           primes[primesSz++]=i;
        }
    }
    scanf("%lld %lld", &k, &n);
    dp = calloc(n+1, sizeof(ll)); fill(dp, n-1, -1);
    dp[1] = 42;
    dp[2] = 11 * k + 77;
    for(int t = 3; t <= n; t++)
        dp[t] = 2*dp[t-1] - dp[t-2] + 10*k;
    int ans = 0;
    for(int i = 1; i <= n; i++)
        if(getprime(dp[i]) == 2)
            ans++;
    printf("%d\n", ans);
    return 0;
}

