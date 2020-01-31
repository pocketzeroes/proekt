#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int main(){
  double x, ym, yM;
  scanf("%lf %lf %lf", &x, &ym, &yM);
  x = (x / 10.0) * (x / 10.0);
  int minn = 10000000;
  int maxx = 0;
  for(int k = 0; k < 1000000; k++){
    double t = 10.0 * sqrt(x);
    double y = ceil(t);
    if(ym <= y && y <= yM){
      minn = fmin(minn, k);
      maxx = fmax(maxx, k);
    }
    x = t;
  }
  if(minn > maxx)
    puts("impossible");
  else if (maxx == 1000000 - 1)
    printf("%d inf\n", minn);
  else
    printf("%d %d\n", minn, maxx);
  return 0;
}
