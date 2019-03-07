#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;

int main(){
  int n;
  scanf("%d", &n);
  ll t = 0, ans = 0;
  for(int i=0; i<n; i++){
    ll x;
    scanf("%lld", &x);
    ans += x*t;
    t += x;
  }
  printf("%lld\n", ans);
  return 0;
}
