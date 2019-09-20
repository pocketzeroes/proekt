#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;

int tot;
int bet[2001][51][51];
int val[2001][51][51];

int Val(int m, int n, int k);

int Bet(int m, int n, int k){
  if(!k || !n || !m)
    return m;
  Val(m, n, k);
  return bet[m][n][k];
}
int Val(int m, int n, int k){
  if(m >= tot)
    return tot;
  if(!k || !n || !m)
    return fminl((ll)tot, m*(1LL << n));
#define res val[m][n][k]
  if(res == 0){
    res = m;
    int mlo = Bet(m-1, n, k), 
        mhi = fmin(m, tot-m);
    if(mlo > mhi)
       mlo = mhi;
    bet[m][n][k] = mlo;
    for (int b = mlo; b <= mhi; ++b) {
      int v = fmin(Val(m-b, n-1, k-1), Val(m+b, n-1, k));
      if(v < res) 
        break;
      bet[m][n][k] = b;
      res = v;
    }
  }
  return res;
  #undef res
}
int main(){
  int md, mg, n, k;
  scanf("%d%d%d%d", &md, &mg, &n, &k);
  tot = md + mg;
  memset(val, 0, sizeof(val));
  printf("%d\n", Val(md, n, n-k));
  return 0;
}
