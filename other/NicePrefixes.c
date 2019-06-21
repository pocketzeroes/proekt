#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;

enum{ MOD = 1000000007};

ll L;
int K;
ll dp[2][101];

int dodp(int l){
  for(int i=(0); i<(l); ++i){
    int i1 = i%2, 
        i2 = (i+1)%2;
    memset(dp[i2], 0, sizeof(dp[i2]));
    for(int k2=(0); k2<(K+1); ++k2){
      int k1 = ((i-2*k2)%K+K)%K;
      int k0 = K-k1-k2;
      if(k0+k1+k2 > K) 
        continue;
      if(k0 < 1) 
        continue;
      int k0p = k0-1, 
          k1p = k1+1, 
          k2p = k2;
      if (k0p == 0) 
        k1p = k2p, k2p = 0;
      dp[i2][k2p] = (dp[i2][k2p] + k0*dp[i1][k2])%MOD;
      if (k1 > 0){
        k1p = k1-1, 
        k2p = k2+1;
        dp[i2][k2p] = (dp[i2][k2p] + k1*dp[i1][k2])%MOD;
      }
    }
  }
  return l%2;
}
typedef struct{
  ll dat[101][101];
}Matrix;
Matrix newMatrix(){
  Matrix rez;
  memset(rez.dat, 0, sizeof(rez.dat));
  for(int k=0; k<K+1; ++k)
    rez.dat[k][k] = 1;
  return rez;
}
Matrix matmul(Matrix first, Matrix second){
  Matrix C = newMatrix();
  for(int i=(0); i<(K+1); ++i){
    for(int j=(0); j<(K+1); ++j){
      C.dat[i][j] = 0;
      for(int k=(0); k<(K+1); ++k)
        C.dat[i][j] = (C.dat[i][j] + first.dat[i][k]*second.dat[k][j]) % MOD;
    }
  }
  return C;
}
Matrix expmod(Matrix X, ll n){
  Matrix ret = newMatrix();
  while (n){
    if (n%2) 
      ret = matmul(ret, X);
    X = matmul(X, X);
    n /= 2;
  }
  return ret;
}
int main(){
  scanf("%lld %d", &L, &K);
  ll matpart = L/K;
  Matrix X = newMatrix();
  for(int k=(0); k<(K+1); ++k){
    memset(dp, 0, sizeof(dp));
    dp[0][k] = 1;
    int idx = dodp(K);
    for(int kp=(0); kp<(K+1); ++kp)
      X.dat[kp][k] = dp[idx][kp];
  }
  Matrix Y = expmod(X, matpart);
  memset(dp, 0, sizeof(dp));
  for(int k=(0); k<(K+1); ++k) 
    dp[0][k] = Y.dat[k][0];
  ll extpart = L-K*matpart;
  int finidx = dodp(extpart);
  ll ans = 0;
  for(int k2=(0); k2<(K+1); ++k2) 
    ans = (ans + dp[finidx][k2]) % MOD;
  printf("%lld\n", ans);
  return 0;
}
