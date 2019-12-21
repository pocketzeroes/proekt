#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
#define EPS 1e-9
typedef long long ll;

int main(){
  int N;
  while(scanf("%d", &N)==1){
    int vx[N+1]; clr(vx);
    int vy[N+1]; clr(vy);
    int mnx =  1000000000,
        mxx = -1000000000;
    for(int i = 0; i < N; i++){
      scanf("%d %d", &vx[i], &vy[i]);
      if(vy[i] == 0){
        mnx = fmin(mnx, vx[i]);
        mxx = fmax(mxx, vx[i]);
      }
    }
    vx[N] = vx[0];
    vy[N] = vy[0];
    double tcx = 0,
           tar = 0;
    for(int i=0; i<N; i++){
      double ar = (vx[i]*vy[i+1] - vy[i]*vx[i+1]) / 2.0;
      double cx = (vx[i] + vx[i+1]) / 3.0;
      double cy = (vy[i] + vy[i+1]) / 3.0;
      tcx += cx * ar;
      tar += ar;
    }
    if(tar < 0.0){
      tar = -tar;
      tcx = -tcx;
    }
    double cx = tcx / tar;
    if(cx < mnx-EPS && vx[0] <= mnx || cx > mxx+EPS && vx[0] >= mxx)
      puts("unstable");
    else{
      if(cx < mnx-EPS){
        double a = tar * (mnx-cx) / (vx[0]-mnx);
        printf("%lld .. ", (ll)(a+EPS) );
      }
      else if (cx > mxx+EPS) {
        double a = tar * (cx-mxx) / (mxx-vx[0]);
        printf("%lld .. ", (ll)(a+EPS) );
      }
      else
        printf("0 .. ");
      if(vx[0] >= mnx && vx[0] <= mxx)
        puts("inf");
      else if(vx[0] > mxx){
        double b = tar * (mxx-cx) / (vx[0]-mxx);
        printf("%lld\n", (ll)(b+1-EPS) );
      }
      else {
        double b = tar * (cx-mnx) / (mnx-vx[0]);
        printf("%lld\n", (ll)(b+1-EPS) );
      }
    }
  }
  return 0;
}
