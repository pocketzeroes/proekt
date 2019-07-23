#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define swap(a,b) do{ typeof(a) tmp; tmp = a; a = b; b = tmp; }while(0)
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
typedef long long ll;

ll xgcd(ll a, ll b, ll*x, ll*y){
  if(b == 0){
   *x = 1;
   *y = 0;
    return a;
  }
  ll g = xgcd(b, a%b, x, y);
  swap(*x, *y);
 (*y) -= (a/b) * (*x);
  return g;
}
ll ceil_div(ll x,ll y){
  if(x<0)
    return x/y;
  else
    return (x+y-1)/y;
}
int main(){
  int T; 
  scanf("%d", &T);
  for(int tc=1; tc<=T; tc++){
    ll R, S, Q;
    scanf("%lld%lld%lld", &R, &S, &Q);
    ll A, B;
    ll g = xgcd(R, -S, &A, &B);
    B = -B;
    A *= Q/g; 
    B *= Q/g;
    ll k = max(ceil_div(1-A,-S/g),ceil_div(1-B,R/g));
    printf("%lld %lld\n", A+k*(-S/g), B+k*(R/g) );
  }
  return 0;
}
