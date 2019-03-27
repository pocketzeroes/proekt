#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
double min(double a, double b){return a<b?a:b;}
double max(double a, double b){return a>b?a:b;}

enum{ ray_speed = 200  };
enum{ width     = 1024 };
enum{ height    = 768  };
enum{ timeout   = 10000};
const double eps = 1e-6;

double find_teh_secret_time_of_fire(int rx, int ry, int W, int H, int n, int*x, int*y, int*vx, int*vy){
  double t = 0;
  double ext_time = max(1.0*rx / ray_speed, 1.0*(W-rx) / ray_speed);
  int fine = 0, pos = 0;
  while (t <= timeout && fine < n){
    for (double curt = t; curt < t + ext_time && t <= timeout; ){
      int wx = vx[pos], wy = vy[pos];
      double cx = fmod(x[pos] + wx * curt, 2*W);
      double cy = fmod(y[pos] + wy * curt, 2*H);
      if (cx < 0) cx = -cx, wx = -wx;
      if (cy < 0) cy = -cy, wy = -wy;
      if (cx > W) cx = 2*W - cx, wx = -wx;
      if (cy > H) cy = 2*H - cy, wy = -wy;
      double dt = (ry - cy) / wy;
      if (fabs(dt) < eps){
        if ((curt - t)*ray_speed > fabs(cx - rx) + eps)
          curt = t = curt - fabs(cx - rx) / ray_speed, fine = 0;
        else
          curt += 2*eps;
      }
      else if (dt < 0){
        if (wy > 0)
          curt += (H-cy) / wy + 2*eps;
        else
          curt += -cy/wy + 2*eps;
      }
      else
        curt += dt;
    }
    ++fine;
    ++pos;
    pos %= n;
  }
  return t;
}
int main(){
  for (int n; scanf("%d", &n) && n; ){
    int rx, ry;
    int x[30], y[30], vx[30], vy[30];
    scanf("%d%d", &rx, &ry);
    for (int i = 0; i < n; ++i)
      scanf("%d %d %d %d", x+i, y+i, vx+i, vy+i);
    double ans = min(find_teh_secret_time_of_fire(rx, ry, width, height, n, x, y, vx, vy),
                     find_teh_secret_time_of_fire(ry, rx, height, width, n, y, x, vy, vx));
    if (ans > timeout)
      printf("Never\n");
    else
      printf("%.9lf\n", ans);
  }
  return 0;
}
