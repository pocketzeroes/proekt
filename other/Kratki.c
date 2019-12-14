#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int main(){
  int n, k;
  scanf("%d %d", &n, &k);
  if(k*1LL*k*1LL < n)
    return puts("-1")*0;
  for(int i = n; i >= 1; i -= k)
    for(int j = fmax(1, i - k + 1); j <= i; ++j)
      printf("%d ", j);
  puts("");
  return 0;
}
