#include <stdio.h>
typedef long long ll;
enum{ MOD = 1000000007};
int n,k;

int modexp(int a, int b, int c){
  if (b==0)
    return 1;
  ll tmp = modexp(a,b/2,c);
  tmp = (tmp * tmp) % c;
  if ((b%2)==1)
    tmp = (tmp * a) % c;
  return (int)tmp;
}
int main(){
  int i;
  ll sum = 0;
  ll talj, namn;
  scanf("%d %d",&n,&k);
  talj = k;
  namn = 1;
  for (i=2;i<=k;i++) {
    ll tmp = modexp(i-1,n-1,MOD);
    tmp = (tmp * i) % MOD;
    talj = (talj * (k-i+1)) % MOD;
    namn = (namn * modexp(i,MOD-2,MOD)) % MOD;
    tmp = (tmp * talj) % MOD;
    tmp = (tmp * namn) % MOD;
    if ((k-i) % 2 == 1)
      tmp = MOD-tmp;
    sum = (sum + tmp) % MOD;
  }
  printf("%lld\n", sum);
  return 0;
}
