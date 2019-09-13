#include<stdio.h>
#include<math.h>

int main(){
  int m;
  double D,d,s;
  for (scanf("%d", &m); m; --m) {
    scanf("%lf%lf%lf", &D, &d, &s);
    printf("%1.0lf\n", floor(M_PI/asin((s+d)/(D-d))));
  }
  return 0;
}
