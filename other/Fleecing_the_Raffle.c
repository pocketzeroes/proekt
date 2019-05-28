#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long double ld;

int main(){
  int n, p;
  scanf("%d%d", &n, &p);
  ld best = (ld)1.0*p/(n+1);
  ld prod = (ld)p/(n+1);
  int bestm = 1;
  for (int m = 2; m <= 2*n; ++m) {
    prod *= (ld)1.0*(n-p+m)/(n+m);
    ld val = prod*m;
    if (val > best) {
      best = val;
      bestm = m;
    } 
  }
  printf("%.11Lf\n", best);
  return 0;
}
