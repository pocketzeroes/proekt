#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;

typedef struct{
  ll first, second;
}pll;
pll newpair(int a, int b){
  return(pll){a,b};
}
typedef struct{
  pll first;
  ll  second;
}trip;
trip newtrip(pll a, ll b){
  return(trip){a,b};
}

#define f first
#define s second

int kase;

ll a [2], n [2];
pll ret;
//trip{pll, ll}

trip extendedGCD(ll a, ll b){
  if(b == 0)
    return newtrip(newpair(1, 0), a);
  trip temp = extendedGCD(b, a%b);
  return newtrip(newpair(temp.f.s, temp.f.f-a/b*temp.f.s), temp.s);
}
int main(){
  scanf("%d", &kase);
  for(int kk=1; kk<=kase; kk++){
    for(int i=0; i<2; i++)
      scanf("%lld %lld", &a[i], &n[i]);
    ret = newpair(a[0], n[0]);
    for(int i=1; i<2; i++){
      trip nexty = extendedGCD(ret.s, n[i]);
      ll x = nexty.f.f,
         d = nexty.s;
      if((a[i]-ret.f)%d != 0){
        ret.f = -1;
        break;
      }
      ret.f += (x*(a[i]-ret.f)/d)%(n[i]/d)*ret.s;
      ret.s = ret.s*(n[i]/d);
      ret.f %= ret.s;
      if(ret.f < 0)
        ret.f += ret.s;
    }
    if(ret.f != -1)
      printf("%lld %lld\n", ret.f, ret.s);
    else
      puts("no solution");
  }
  return 0;
}
