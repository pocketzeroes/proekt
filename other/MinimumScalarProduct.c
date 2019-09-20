#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
int T, N;
ll all[2][1005];

int cmpLL(const void*pa, const void*pb){
  ll*a =(ll*)pa;
  ll*b =(ll*)pb;
  return(*a < *b)?-1:1;
}
int main() {
    int i, Case = 1;
    scanf("%d", &T);
    while (T --) {
      scanf("%d", &N);
      for (i = 0; i < N; i ++)
      scanf("%lld", &all[0][i]);
      for (i = 0; i < N; i ++)
      scanf("%lld", &all[1][i]);
      qsort(all[0], N, sizeof(ll), cmpLL);
      qsort(all[1], N, sizeof(ll), cmpLL);
      ll ret = 0;
      for (i = 0; i < N; i ++)
      ret += all[0][i] * all[1][N - 1 - i];
      printf("Case #%d: %lld\n", Case ++, ret);
    }
    return 0;
}
