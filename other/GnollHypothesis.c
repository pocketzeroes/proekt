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
  int mul_sz=n-k+1;
  double mul[mul_sz];
  mul[0] = k/(double)(n);
  for(int i=1; i<mul_sz; ++i)
    mul[i] = mul[i-1]*(n-k-i+1)/(n-i);
  double s[n];
  for(int i=0; i<n; ++i)
    scanf("%lf", &s[i]);
  for(int i=0; i<n; ++i){
    double res=0;
    for(int j=0; j<mul_sz; ++j){
      int idx = (n + i - j) % n;
      res += mul[j] * s[idx];
    }
    printf("%.9lf", res);
    printf(i + 1 < n ? " " : "\n");
  }
  return 0;
}
