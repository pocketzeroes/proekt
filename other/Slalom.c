#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))

const double eps = 1e-9,
        infinity = 1e300;

typedef struct{
  double x, y;
}pt;
pt newpt(double X, double Y){
  pt rez;
  rez.x = X;
  rez.y = Y;
  return rez;
}

double area2(pt a, pt b, pt c){
  return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}
bool leftturn(pt a, pt b, pt c){
  return area2(a, b, c) > eps;
}
bool norightturn(pt a, pt b, pt c){
  return area2(a, b, c) > -eps;
}
double dist(pt a, pt b){
  return hypot(a.x - b.x, a.y - b.y);
}
pt intersect(pt p, pt q, double y){
  double dx = q.x - p.x, 
         dy = q.y - p.y;
  return newpt(p.x + dx / dy * (y - p.y), y);
}
int main(){
  int n;
  while (scanf("%i", &n) == 1 && n != 0){
    pt interv[n + 1][2];
    double f[n + 1][2];
    pt p, e[2];
    scanf("%lf %lf\n", &p.x, &p.y);
    interv[0][0] = interv[0][1] = newpt(p.x, p.y);
    for (int i = 1; i <= n; ++i) {
      double y, x1, x2;
      scanf("%lf %lf %lf\n", &y, &x1, &x2);
      interv[i][0] = newpt(x1, y);
      interv[i][1] = newpt(x2, y);
    }
    f[n][0] = f[n][1] = 0;
    for (int i = n - 1; i >= 0; --i)
      for (int side = 0; side < 2; ++side) {
        pt p = interv[i][side];
        e[0] = interv[i + 1][0];
        e[1] = interv[i + 1][1];
        int j;
        f[i][side] = infinity;
        for (j = i + 1; j <= n; ++j) {
          if (leftturn(p, interv[j][1], e[0]) || leftturn(p, e[1], interv[j][0]))
            break;
          else {
            if (norightturn(p, e[0], interv[j][0])) {
              e[0] = interv[j][0];
              f[i][side] = min(f[i][side], dist(p, interv[j][0]) + f[j][0]);
            }
            if (norightturn(p, interv[j][1], e[1])) {
              e[1] = interv[j][1];
              f[i][side] = min(f[i][side], dist(p, interv[j][1]) + f[j][1]);
            }
          }
        }
        assert(j > i + 1);
        if (j > n) {
          double y = interv[n][0].y;
          e[0] = intersect(p, e[0], y);
          e[1] = intersect(p, e[1], y);
          double d;
          if (p.x > e[1].x) d = dist(p, e[1]);
          else if (p.x < e[0].x) d = dist(p, e[0]);
          else d = p.y - e[0].y;
          f[i][side] = min(f[i][side], d);
        }
        if (i == 0) 
          break;
      }
    printf("%.11lf\n", f[0][0]);
  }
  return 0;
}
