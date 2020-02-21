#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>



typedef long long ll;
typedef struct{
  ll x, y;
}pll;
pll newpll(int a, int b){
  return(pll){a,b};
}
int cmpP(const void*pa, const void*pb){
  pll*a = (pll*)pa;
  pll*b = (pll*)pb;
  if(a->x  != b->x) return(a->x  < b->x )?-1:1;
  if(a->y != b->y)return(a->y < b->y)?-1:1;
  return 0;
}

static inline void rd(int*x){
  int k;
  int m=0;
 *x=0;
  for(;;){
    k = getchar_unlocked();
    if(k=='-'){
      m=1;
      break;
    }
    if('0'<=k&&k<='9'){
     *x=k-'0';
      break;
    }
  }
  for(;;){
    k = getchar_unlocked();
    if(k<'0'||k>'9'){
      break;
    }
    *x = (*x)*10+k-'0';
  }
  if(m){
    *x = -(*x);
  }
}
static inline void rdl(ll*x){
  int k;
  int m=0;
 *x=0;
  for(;;){
    k = getchar_unlocked();
    if(k=='-'){
      m=1;
      break;
    }
    if('0'<=k&&k<='9'){
      *x = k-'0';
      break;
    }
  }
  for(;;){
    k = getchar_unlocked();
    if(k<'0'||k>'9'){
      break;
    }
    *x = (*x)*10+k-'0';
  }
  if(m){
    *x = -(*x);
  }
}
static inline void wt_L(char a){
  putchar_unlocked(a);
}
static inline void wt_Ls(const char c[]){
  int i=0;
  for(i=0;c[i]!='\0';i++){
    putchar_unlocked(c[i]);
  }
}
static inline ll moddw_L(ll a, ll b){
  a %= b;
  if(a < 0)
    a += b;
  return a;
}
int N;
ll X[100000];
ll Y[100000];
ll QX;
ll QY;
pll xy[100000];
ll k;
int main(){
  int e98WHCEY;
  rd(&N);
  {
    int Lj4PdHRW;
    for(Lj4PdHRW=(0);Lj4PdHRW<(N);Lj4PdHRW++){
      rdl(&X[Lj4PdHRW]);
      rdl(&Y[Lj4PdHRW]);
    }
  }
  int cTE1_r3A;
  rd(&cTE1_r3A);
  for(e98WHCEY=(0);e98WHCEY<(cTE1_r3A);e98WHCEY++){
    int i;
    rdl(&QX);
    rdl(&QY);
    if(N%2){
      wt_Ls("NO");
      wt_L('\n');
      continue;
    }
    if(QX < 0){
      {
        int xr20shxY = (-1);
        QX *= xr20shxY;
        QY *= xr20shxY;
      }
    }
    if(QX==0 && QY < 0){
      {
        int WYIGIcGE = (-1);
        QX *= WYIGIcGE;
        QY *= WYIGIcGE;
      }
    }
    if(QX == QY  &&  QY == 0){
      wt_Ls("NO");
      wt_L('\n');
      continue;
    }
    for(i=0; i<N; i++){
      if(QX){
        k = X[i] / QX;
        while(X[i] - k * QX < 0)
          k--;
        while(X[i] - k * QX >= QX)
          k++;
        xy[i].x = X[i] - k * QX;
        xy[i].y = Y[i] - k * QY;
      }
      else{
        xy[i].x = X[i];
        xy[i].y = moddw_L(Y[i], QY);
      }
    }
    qsort(xy, N, sizeof(pll), cmpP);
    for(i=0; i<N; i+=2){
      if(xy[i].x != xy[i+1].x||
         xy[i].y != xy[i+1].y){
        wt_Ls("NO");
        wt_L('\n');
        goto RZTsC2BF;
      }
    }
    wt_Ls("YES");
    wt_L('\n');
  RZTsC2BF:;
  }
  return 0;
}
