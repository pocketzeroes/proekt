#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
ll min(ll a, ll b){return a<b?a:b;}
ll max(ll a, ll b){return a>b?a:b;}
void fill(ll*arr, int sz, ll val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}

int main(){
  ll N, H, HC, DC;
  while(scanf("%lld %lld %lld %lld", &N, &H, &HC, &DC)==4){
    ll X[N];
    ll Y[N];
    for(int i=0; i<N; i++)
      scanf("%lld %lld", &X[i], &Y[i]);
    ll cost[N];
    fill(cost, N, (ll)1e18);
    cost[0] = HC*(H-Y[0]);
    for(int i=0; i < N; i++){
      ll mind = 0, 
         maxd = 2*(H-Y[i]);
      for(int j = i+1; j < N; j++){
        ll d = X[j]-X[i], 
           h = H-Y[j];
        if(d > maxd)
          break;
        if(2*h <= d)
          mind = max(mind, 2*d+2*h-(ll)(sqrt(8*d*h)));
        maxd = min(maxd, 2*d+2*h+(ll)(sqrt(8*d*h)));
        if(mind > maxd)
          break;
        if(d >= mind && d <= maxd)
          cost[j] = min(cost[j], cost[i] + HC*h + DC*d*d);
      }
    }
    if(cost[N-1] == (ll)1e18)
      puts("impossible");
    else
      printf("%lld\n", cost[N-1]);
  }
  return 0;
}
