#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;

int qr[600000];

int Exp(int p, int e){
  int P = 1;
  for (int i = 0; i < e; ++i) 
    P *= p;
  return P;
}
ll powsols(int p, int e) {
  int P = Exp(p, e);
  ll res = 0;
  memset(qr, 0, sizeof(qr));
  for (int i = 0; i < P; ++i) 
    ++qr[(ll)i*i % P];
  for (int i = 0; i < P; ++i) 
    res += qr[i]*qr[(i+1)%P];
  for (int i = 0, sq = 0; i < P; i += p, sq = (ll)i*i % P) 
    res += qr[(sq+1)%P];
  res *= P/p*(p-1);
  if (e > 1) 
    res += powsols(p, e-2)*p*p*p;
  else
    ++res;
  return res;
}
ll zeros(int n){
  ll res = 1+3*qr[0];
  for (int i = 0; i < n; ++i)
    res += qr[i]*(2*qr[i] + qr[(n-i)%n]);
  return res;
}
ll diag(int n){
  ll res = 0;
  for (int i = 1; i < n; ++i)
    res += qr[(ll)2*i*i % n];
  return res;
}
int main(){
  int N, n;
  scanf("%d", &n);
  N = n;
  long long res = 1;
  for (int p = 2; p*p <= n; ++p)
    if (n % p == 0) {
      int e = 0;
      while (n % p == 0) ++e, n /= p;
      res *= powsols(p, e);
    }
  if (n != 1)
    res *= powsols(n, 1);
  memset(qr, 0, sizeof(qr));
  for (int i = 1; i < N; ++i)
    ++qr[(long long)i*i % N];
  res -= zeros(N);
  res += diag(N);
  printf("%lld\n", res/2);
  return 0;
}
