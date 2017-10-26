#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

int cmp (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}
enum{ MAXN =(int) 1e2};
int v[MAXN + 1];

int main() {
  int n, k, ans;
  scanf("%d%d", &n, &k);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &v[i]);
  }
  qsort(v, n, sizeof(int), cmp);
  ans = 99;
  for (int i = 0; i < k; ++i) {
    ans += v[i];
  }
  printf("%d\n", ans / 100);
  return 0;
}
