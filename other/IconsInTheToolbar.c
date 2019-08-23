#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
ll min(ll a, ll b){return a<b?a:b;}

int N, x[2000000];
ll sum1[2000001], sum2[2000002];

int main(){
  scanf("%d", &N);
  sum1[0] = sum2[0] = 0;
  for (int i = 0; i < 2*N; ++i){
    scanf("%d", x+i);
    sum1[i+1] = sum1[i] + x[i];
    sum2[i+2] = sum2[i] + x[i];
  }
  ll ans = 1LL<<60;
  for(int cut = 1; cut <= N; ++cut)
    ans = min(ans, (sum1[cut] + sum2[2*N] - sum2[2*cut])*(x[0] +x[cut]));
  printf("%lld\n", ans);
  return 0;
}
