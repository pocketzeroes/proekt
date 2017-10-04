#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

enum{ N   =(int) 1e5 + 5}; 
enum{ mod =(int) 1e9 + 7};
int d[N];

int main() {
  int n, k;
  scanf("%d %d", &n, &k);
  for (int i = 1; i < n; i++) {
    int u, v;
    scanf("%d %d", &u, &v);
    d[u]++;
    d[v]++;
  }
  long long ans = k;
  for (int i = 1; i <= n; i++) {
    int now = k-1, ch = d[i];
    if (i != 1)
      now--, ch--;
    while (ch--) {
      ans = (ans * now--) % mod;
    }
  }
  printf("%lld\n", ans);
  return 0;
}
