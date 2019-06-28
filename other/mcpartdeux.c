#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
#include<complex.h>
#define swap(a,b) do{int tmp; tmp = a; a = b; b = tmp; }while(0)
typedef long long ll;
typedef long long complex cpx;

#define CMPLX(x,y) __builtin_complex((double)(x), (double)(y))



int n,m;
int  as[1000], bs[1000], cs[1000], xs[1000], ys[1000], zs[1000];
bool known[1000];
cpx pts[1000];

ll norm(complex p){
  ll cr = creal(p);
  ll ci = cimag(p);
  return cr*cr + ci*ci;
}
void put(int i, int x, int y){
  known[i] = 1;
  pts[i] = CMPLX(x,y);
}
int main(){
  scanf("%d %d", &n, &m);
  if (n==0)
    exit(0);
  for(int i=(0); i<(n); ++i){
    scanf("%d %d %d %d %d %d", &as[i], &bs[i], &cs[i], &xs[i], &ys[i], &zs[i]);
    --as[i], --bs[i], --cs[i];
  }
  memset(known,0,sizeof(known));
  put(0, 0, 0);
  put(1, 0, 1);
  put(2, 1, 0);
  while(1){
    bool done = 1;
    for(int i=(0); i<(n); ++i){
      int nk = known[as[i]] + known[bs[i]] + known[cs[i]];
      if (nk == 2){
        done = 0;
        while(known[bs[i]]){
          swap(as[i], cs[i]);
          swap(as[i], bs[i]);
          swap(xs[i], zs[i]);
          swap(xs[i], ys[i]);
        }
        int a = as[i],
            b = bs[i],
            c = cs[i];
        cpx p = pts[a],
            q = pts[c];
        for (ll dx = 0; dx*dx <= xs[i]; ++dx){
          ll dy = (ll)(sqrt(xs[i]-dx*dx)+0.5);
          if (dx*dx+dy*dy != xs[i])
            continue;
          for(int zz=(0); zz<(2); ++zz){
            dx *= -1;
            for(int zzz=(0); zzz<(2); ++zzz){
              dy *= -1;
              cpx r = p + CMPLX(dx, dy);
              if(ys[i] == norm(q-r) && cimag(conj(q-r)*(r-p)) < 0)
                put(b, creal(r), cimag(r));
            }
          }
        }
      }
    }
    if(done)
      break;
  }
  for(int i=0; i<m; ++i)
    printf("%.0lf %.0lf\n", creal(pts[i]), cimag(pts[i]));
  return 0;
}
