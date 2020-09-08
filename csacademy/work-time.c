#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int cmp(const void * a, const void * b){ return ( *(int*)a - *(int*)b ); }
enum{N = 100100};
int n, a[N], x, t, b[N];

char*solve(){
  scanf("%d %d", &n, &x);
  for(int i = 1; i <= n; i++)
    scanf("%d", &a[i]), a[i] = fmin(a[i], a[i] ^ x);
  for(int i = 1; i <= n; i++)
    scanf("%d", &b[i]), b[i] = fmin(b[i], b[i] ^ x);
  qsort(a+1, n, sizeof(int), cmp);
  qsort(b+1, n, sizeof(int), cmp);
  for(int i=1; i<=n; i++)
    if(a[i]!=b[i])
      return"No\n";
  return"Yes\n";
}
int main(){
  scanf("%d", &t);
  while(t--)
    puts(solve());
  return 0;
} 
