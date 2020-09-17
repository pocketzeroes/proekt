#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define swap(a,b) do{ __typeof(a) tp; tp=a; a=b; b=tp; }while(0)
typedef long long ll;
static inline ll min(ll a, ll b){return a<b?a:b;}

ll gcd(ll a, ll b){
   ll c = a % b;
   while(c > 0){
        a = b;
        b = c;
        c = a % b;
   }
   return b;
}
int main(){
    ll A, B, C, D, N;
    scanf("%lld %lld %lld %lld %lld", &N, &A, &B, &C, &D);
    if(B*C > D*A){
        swap(A, C);
        swap(B, D);
    }
    ll ans = (N + A-1)/A*B;
    ll n = A/gcd(A, C);
    for(ll i=1; i<n; i++){
        ll t = i*D;
        if(N-C*i>0)
            t+= (N - C*i + A-1)/A * B;
        ans = min(ans, t);
    }
    printf("%lld\n", ans);
    return 0;
}
