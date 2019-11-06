#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
enum{ MAXN = 40};
int n;
ll coef[MAXN];

ll gcd(ll a, ll b){
    return b == 0 ? a : gcd(b, a % b);
}
int main(){
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
        scanf("%lld", &coef[i]);
    ll nu = coef[n-1];
    ll de = 1;
    for(int i = n-2; i >= 0; i--){
        ll od = de;
        de = nu;
        nu = od;
        nu += coef[i]*de;
        ll di = gcd(de, nu);
        nu /= di;
        de /= di;
    }
    printf("%lld/%lld\n", nu, de);
    return 0;
}
