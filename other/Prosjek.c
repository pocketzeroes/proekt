#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))

typedef long double ld;
enum{ MAXN = 300010};
ld  s[MAXN];
int a[MAXN];
int n, k;

bool can(ld P){
  s[0] = 0;
  for (int i = 1; i <= n; ++i)
    s[i] = s[i-1] + a[i] - P;
  ld mins = 0;
  for (int i = k; i <= n; ++i){
    if (s[i] >= mins)
      return true;
    mins = min(mins, s[i-k+1]);
  }
  return false;
}
int main(){
  scanf("%d %d", &n, &k);
  for(int i = 1; i <= n; ++i)
    scanf("%d", &a[i]);
  ld lo = 0, 
     hi = 2e6;
  while(hi-lo > 1e-6){
    ld mid = (lo + hi) / 2;
    if(can(mid))
      lo = mid;
    else
      hi = mid;
  }
  printf("%.6lf\n", (double)lo);
  return 0;
}
