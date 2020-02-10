#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int main(){
  int n1, n2, n12;
  scanf("%d %d %d", &n1, &n2, &n12);
  int N = floor(((n1+1)*(n2+1)/(n12+1) )-1);
  printf("%d\n", N);
  return 0;
}
