#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef struct{
  double first, second;
}pt;
pt newpt(double a, double b){
  return(pt){a,b};
}
typedef struct{
  double first;
  int    second;
}pdi;
pdi newpdi(double a, int b){
  return(pdi){a,b};
}
int cmpPdi(const void*pa, const void*pb){
  pdi*a=(pdi*)pa;
  pdi*b=(pdi*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}
//////////////////////////////////////
double EPS     = 1e-9;
double EPS_RAD = 5e-6;
double RMAX    = 1e6;
#define _x_ first
#define _y_ second
int N;
pt*Pts;
int psz;

bool angular_interval(double R, pt*P, double*al, double*ar){
  double x = P->_x_,
         y = P->_y_;
  if(x*x+y*y > 4.*R*R)
    return false;
  double xm   = x/2.,
         ym   = y/2.;
  double norm = sqrt(x*x+y*y);
  double vx   =  y/norm,
         vy   = -x/norm;
  double h    = sqrt(R*R-(xm*xm+ym*ym));
  double xl   = xm+h*vx,
         yl   = ym+h*vy;
  double xr   = xm-h*vx,
         yr   = ym-h*vy;
 *al = atan2(yl,xl);
 *ar = atan2(yr,xr);
  return true;
}
int best_fire(double R){
  pdi*I=calloc(2*N, sizeof(pdi));
  int isz = 0;
  int cnt = 0,
      res = 0;
  for(int z=0;z<psz;z++){pt P = Pts[z];
    double al, ar;
    if(angular_interval(R, &P, &al, &ar)){
      if(al<ar){
        I[isz++]=newpdi(al-EPS, 1);
        I[isz++]=newpdi(ar+EPS,-1);
      }
      else{
        I[isz++]=newpdi(al-EPS, 1); ++cnt;
        I[isz++]=newpdi(ar+EPS,-1);
      }
    }
  }
  qsort(I, isz, sizeof(pdi), cmpPdi);
  for(int z=0;z<isz;z++){pdi it=I[z];
    cnt += it.second;
    res = fmax(res, cnt);
  }
  return res;
}
int main(){
  int K;
  scanf("%d %d", &N, &K);
  Pts = calloc(N, sizeof(pt));
  psz = N;
  for(int i=0; i<N; ++i){
    int x, y;
    scanf("%d %d", &x, &y);
    Pts[i] = newpt(x, y);
  }
  double Rmin = 0.,
         Rmax = RMAX;
  if(best_fire(Rmax)<K)
    puts("-1");
  else{
    while(Rmax-Rmin>EPS_RAD){
      double R=(Rmin+Rmax)/2.;
      if(best_fire(R)>=K)
        Rmax = R;
      else
        Rmin = R;
    }
    printf("%lf\n", Rmax);
  }
  return 0;
}
