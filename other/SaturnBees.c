#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;

bool cancycle(ll odd, int veven){
  ll round=(odd+1)&~(2ll);
  int vodd = __builtin_ctzll(round);
  return veven>vodd;
}
bool tiling(ll n, ll m){
  int vn = __builtin_ctzll(n);
  int vm = __builtin_ctzll(m);
  if (vm == 1) return false;
  if (vn + vm <= 2) return false;
  if (vn >= 1 && vm >=2) return true;
  if (vn==0) return cancycle(n,vm);
  if (vm==0) return cancycle(m,vn);
  abort();
}
int main(){
  ll n,m;
  scanf("%lld %lld", &n, &m);
  puts(tiling(n,m) ? "possible" : "impossible");
  return 0;
}
