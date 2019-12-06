#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
enum{ maxp = 105};

typedef struct{
  double M[102][102];
  int sz, sz0;
}mat;

mat newmat(int a, int b){
  mat rez;
  clr(rez.M);
  rez.sz =a;
  rez.sz0=b;
  return rez;
}
mat GetIdentity(int n){
  mat ret = newmat(102, 102);
  for(int i=0; i<n; i++)
    ret.M[i][i] = 1;
  return ret;
}

mat opmul(mat M, mat A){
  int a = M.sz;
  int b = M.sz0;
  int c = A.sz0;
  mat R = newmat(a, c);
  for(int i = 0; i < a; i++)
    for(int j = 0; j < c; j++)
      for(int k = 0; k < b; k++)
        R.M[i][j] += M.M[i][k] * A.M[k][j];
  return R;
}
mat oppow(mat X, int p){
  int n = X.sz;
  mat I = GetIdentity(n);
  mat R = I;
  while(p > 0){
    if(p & 1)
      R = opmul(X, R);
    p >>= 1;
    X = opmul(X, X);
  }
  return R;
}

double Exp(double x, int p){
  double ret = 1.0;
  while(p--)
    ret *= x;
  return ret;
}
mat Generate(int n, double p){
  mat M = newmat(102, 102);
  M.M[101][101] = 1.0;
  for(int k=0; k<=100; k++){
    for(int i=0; i<k; i++)
      M.M[k][k - i - 1] = Exp(1.0 - p, i) * p;
    M.M[k][100] = Exp(1.0 - p, k);
    M.M[k][101] = Exp(1.0 - p, k) * 5.0;
  }
  return M;
}
int main(){
  int    n;
  double p;
  scanf("%d %lf", &n, &p);
  mat M = Generate(n, p);
  mat N = oppow(M, n);
  mat v0 = newmat(102, 1);
  for(int i=0; i<102; i++)
    v0.M[i][0] = 1.0;
  mat R = opmul(N, v0);
  double ans = R.M[100][0] - 1.0;
  printf("%.9lf\n", ans);
  return 0;
}
