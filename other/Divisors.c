#include<stdio.h>
#include<stdlib.h>
typedef unsigned long long ull;
typedef unsigned int       u32;

enum{ MAX  = 1000};
enum{ MAXP = (2 * MAX + 1)};
u32 primes [MAXP];
u32 isprime[MAXP];

u32 factpow(u32 n, u32 p){
  u32 d = 0;
  do
  {
    n /= p;
    d+=n;
  }while (n);
  return d;
}
ull ndivs(u32 n, u32 k){
  u32 i, ad;
  ull nd = 1, max = -1;
  max >>= 1;
  for (i = 0; primes[i] <= n; i++){
    ad = factpow (n, primes[i]) - factpow (k, primes[i]) - factpow (n-k, primes[i]);
    if (max / (ad + 1) < nd)
      abort ();
    nd *= (ad + 1);
  }
  return nd;
}
int main(){
  u32 n, k, i, j;
  isprime[1] = 1;
  n = 0;
  for (i = 2; i < MAXP; i++){
    if (!isprime[i]){
      primes[n++] = i;
      for (j = 2 * i; j < MAXP; j += i)
        isprime[j] = 1;
    }
  }
  while (1){
    if (scanf ("%u%u", &n, &k) != 2)
      return 0;
    printf ("%llu\n", ndivs (n, k));
  }
  return 0;
}
