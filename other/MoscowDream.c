#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int main(){
  int a, b, c, n;
  scanf("%d%d%d%d", &a, &b, &c, &n);
  if(a == 0 || b == 0 || c == 0) return puts("NO")*0;
  if(a+b+c < n)                  return puts("NO")*0;
  if(n < 3)                      return puts("NO")*0;
  puts("YES");
  return 0;
}
