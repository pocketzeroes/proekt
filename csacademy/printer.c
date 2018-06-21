#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;

inline void cmin(ll*x, ll y){
    if(y <*x)
      *x = y;
}
inline ll dmax(ll x, ll y){
    return x > y ? x : y;
}
ll a[5], c[5], p;
int main(){
    for(int i=1; i<=4; i++)
      scanf("%lld", &c[i]);
    for(int i=1; i<=4; i++)
      scanf("%lld", &a[i]);
    scanf("%lld", &p);
    ll ans =(ll)2e18;
    for(int i=0; i<=4; i++){
        ll sum = c[i]*p;
        for(int j=1; j<=4; j++)
          sum += dmax(c[j] - c[i], 0LL) * a[j];
        cmin(&ans, sum);
    }
    printf("%lld\n", ans);
    return 0;
}
