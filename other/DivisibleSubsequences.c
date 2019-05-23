#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

long long c[1000100];

void solve(){
  int D, N, s = 0, v;
  scanf("%d%d", &D, &N);
  assert(1 <= D && D <= 1000000);
  assert(1 <= N && N <= 50000);
  memset(c, 0, sizeof(c)); ++c[0];
  for (int i = 0; i < N; ++i) 
    scanf("%d", &v), assert(1 <= v && v <= 1000000000), ++c[s = (s + v) % D];
  long long ans = 0;
  for (int i = 0; i < D; ++i) ans += c[i]*(c[i]-1)/2;
  printf("%lld\n", ans);
}
int main(){
  int T;
  scanf("%d", &T);
  for (int i = 0; i < T; ++i)
    solve();
  return 0;
}
