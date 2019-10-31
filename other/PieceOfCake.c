#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int main(){
  int n, a, b;
  scanf("%d %d %d", &n, &a, &b);
  int ans = 4 * fmax(a, n-a) * fmax(b, n-b);
  printf("%d\n", ans);
  return 0;
}
