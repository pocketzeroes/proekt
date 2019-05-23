#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))


enum{ maxn = 50000};
const double eps = 1e-11, 
        infinity = 1e300;

double px[maxn], 
       py[maxn];
int n;

bool possible(double d, double*px1, double*px2){
  double x1 = -infinity, 
         x2 =  infinity;
  for (int i = 0; i < n; ++i) {
    if (d < py[i])
      return false;
    double p = sqrt(d * d - py[i] * py[i]),
           a = px[i] - p, b = px[i] + p;
    x1 = max(x1, a);
    x2 = min(x2, b);
    if (x1 > x2)
      return false;
  }
 *px1 = x1;
 *px2 = x2;
  return true;
}
int main(){
  while (scanf("%i", &n) == 1 && n > 0){
    double a, b = 0, x1, x2;
    for (int i = 0; i < n; ++i){
      scanf("%lf%lf", &px[i], &py[i]);
      if (py[i] < 0) py[i] = -py[i];
      b = max(b, py[i]);
    }
    if (b == 0) {
      if (n == 1) { printf("%.9lf %.9lf\n", px[0], .0); continue; }
      b = 1;
    }
    while (!possible(b, &x1, &x2)) b *= 2;
    a = b / 2;
    while (possible(a, &x1, &x2)) a /= 2;
    for (int i = 0; i < 100 && (b - a > eps || x2 - x1 > eps); ++i) {
      double m = (a + b) / 2;
      if (possible(m, &x1, &x2))
        b = m;
      else
        a = m;
    }
    printf("%.9lf %.9lf\n", (x1 + x2) / 2, b);
  }
  return 0;
}
