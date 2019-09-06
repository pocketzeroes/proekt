#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
// https://open.kattis.com/problems/qualificationround
typedef long long ll;

int cmpLL(const void*pa, const void*pb){
  ll*a =(ll*)pa;
  ll*b =(ll*)pb;
  return(*a < *b)?-1:1;
}

int main() {
  int K;
  scanf("%d", &K);
  for (int c = 1; c <= K; ++c) {
    int P, C;
    scanf("%d%d", &P, &C);
    ll arr[P];
    for (int i = 0; i < P; ++i){
      scanf("%lld", &arr[i]);
    }
    ll s = 0;
    qsort(arr, P, sizeof(ll), cmpLL);
    int u = P - C;
    for (int i = 0; i < u; ++i)
      s += arr[i];
    while(1){
      int j;
      for (j = u; j < P; ++j)
        if (arr[j] != arr[u])
          break;
      if (j == P) {
        arr[u] += s/(j-u);
        break;
      }
      ll toadd = fminl(arr[j]-arr[u], s/(j-u));
      for (int i = u; i < j; ++i){
        s -= toadd;
        arr[i] += toadd;
      }
      if (s < j-u+1)
        break;
    }
    printf("Case #%d: %lld\n", c, arr[u]);
  }
  return 0;
}
