#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
ll max(ll a, ll b){return a>b?a:b;}

int main(){
  int N, K;
  scanf("%d %d", &N, &K);
  ll ans = 0;
  ll bestCash = 0;
  for(int i=0; i<N; ++i){
    ll price;
    scanf("%lld", &price);
    bestCash = max(bestCash, 100 * price);
    bestCash -= K;
    bestCash = max(bestCash, 0LL);
    ans = max(ans, bestCash - price * 100);
  }
  printf("%lld\n", ans);
  return 0;
}
