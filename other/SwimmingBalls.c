#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long double ld;

enum{ maxn = 10005};

int n;
ld W, L, D, V;
ld w[maxn],
   r[maxn];

ld calcu(ld R, ld X){
  if(X >= R + R)
    return 4 * (ld)(1.0) / 3 * (2 * acosl((ld)0)) * R * R * R;
  else if(X <= R){
    return (2 * acosl((ld)0)) * X * X * (R - X / 3);
  }
  else{
    return 4 * (ld)(1.0) / 3 * (2 * acosl((ld)0)) * R * R * R - calcu(R, R + R - X);
  }
}
ld cal(ld x){
  ld res = x * W * L;
  for(int i = 0; i < (n); ++i){
    ld v = calcu(r[i], x);
    ld vball = 4 * (ld)(1.0) / 3 * (2 * acosl((ld)0)) * r[i] * r[i] * r[i];
    if(v >= vball * w[i])
      res -= vball * w[i];
    else
      res -= v;
  }
  return res;
}
void solve(){
  scanf("%d", &n);
  scanf("%Lf %Lf %Lf %Lf", &W, &L, &D, &V);
  for(int i=0; i<n; i++)
    scanf("%Lf %Lf", &r[i], &w[i]);
  ld l = 0, r = D, mid;
  for(int run = 0; run < 100; run++){
    mid = (l + r) / 2;
    if(cal(mid) <= V)
      l = mid;
    else
      r = mid;
  }
  printf("%.11Lf\n", l);
}
int main(){
  int test;
  scanf("%d", &test);
  for(int itest = 0; itest < (test); ++itest)
    solve();
  return 0;
}
