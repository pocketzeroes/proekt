#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
#define MOD 1000000009ll
int cmpLL(const void*pa, const void*pb){
  ll*a =(ll*)pa;
  ll*b =(ll*)pb;
  return(*a < *b)?-1:1;
}
void fill(ll*arr, int sz, ll val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}

int main(int taskE, char**bapc){
  int n;
  scanf("%d", &n);
  ll A[n];
  for(int i=0; i<n; i++)
    scanf("%lld", &A[i]);
  qsort(A, n, sizeof(ll), cmpLL);
  ll I[n+1];
  fill(I, n+1, 1);
  for(int i=2; i<=n; ++i)
    I[i] = (MOD - (MOD/i) * I[MOD%i] % MOD) % MOD;
  ll T[n][n];
  for(int i=0; i<n; i++)
    fill(T[i], n, 1);
  for(int i=0; i<n; ++i){
    for(int j=i+1, eq=1; j<n; ++j){
      eq = (A[j] == A[j-1] ? eq+1 : 1);
      T[i][j] = T[i][j-1] * (ll)(j-i+1) % MOD * I[eq] % MOD;
    }
  }
  ll U[n]; memset(U, 0, sizeof(U));
  for(int i=1; i<n; ++i){
    U[i] = T[0][i];
    for(int j=0; j<=i; ++j)
      U[i] = (MOD*MOD + U[i] - (j>0?U[j-1]:1LL) * (j<i?T[j+1][i]:1LL)) % MOD;
  }
  printf("%lld\n", U[n-1]);
  return 0;
}
