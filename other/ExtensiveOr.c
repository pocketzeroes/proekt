#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;

int in_nextInt(){
  int xx;
  scanf("%d", &xx);
  return xx;
}
char buff[100005];
char*getstr(){
  int rv = scanf("%s", &buff);
  return strdup(buff);
}

ll**newmat(int x, int y){
  ll**rv = calloc(x, sizeof(ll*));
  for(int i=0;i<x;i++)
    rv[i] = calloc(y, sizeof(ll));
  return rv;
}
////////////////////////
enum{ mod = 1000000007};
char*s;
int N, pN;
int K;
ll**mat;

bool get(int mask, int bit){
  return ((mask >> bit) & 1) == 1;
}
ll**makeMatrix(int v){
  ll**ret = newmat(pN, pN);
  for(int i = 0; i < pN; i++){
    for(int j = 0; j < pN >> 1; j++){
      int bits = (v << N) | (j << 1) | (__builtin_popcount(j) & 1);
      int nextMask = i;
      for(int k = 0; k < N; k++){
        if(get(bits, k) && !get(bits, k+1) && !get(i, k))
          goto outer;
        if(!get(bits, k) && get(bits, k+1))
          nextMask |= 1 << k;
      }
      ret[i][nextMask]++;
  outer:;
    }
  }
  return ret;
}
ll**matrix_mult(ll**A, ll**B){
  ll**C = newmat(pN, pN);
  for(int i = 0; i < pN; i++)
    for (int j = 0; j < pN; j++)
      for (int k = 0; k < pN; k++)
        C[i][k] = (C[i][k] + A[i][j] * B[j][k]) % mod;
  return C;
}
ll**mat_exp(ll**A, int e){
  ll**ret = newmat(pN, pN);
  for (int i = 0; i < pN; i++)
    ret[i][i] = 1;
  while (e > 0){
    if ((e & 1) == 1)
      ret = matrix_mult(ret, A);
    A = matrix_mult(A, A);
    e >>= 1;
  }
  return ret;
}
ll solve(){
  mat = newmat(pN, pN);
  for(int i = 0; i < pN; i++)
    mat[i][i] = 1;
  ll***m = calloc(2, sizeof(ll**));
  m[0] = makeMatrix(0);
  m[1] = makeMatrix(1);
  for(int z=0;s[z];z++){char c=s[z];
    mat = matrix_mult(mat, m[c-'0']);
  }
  mat = mat_exp(mat, K);
  return mat[0][pN-1];
}

int main(){
  N = in_nextInt();
  K = in_nextInt();
  s = getstr();
  pN = 1 << N;
  printf("%lld\n", solve());
  return 0;
}
