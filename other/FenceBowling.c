#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int in_nextInt(){
  int xx;
  scanf("%d", &xx);
  return xx;
}
double in_nextDouble(){
  double xx;
  scanf("%lf", &xx);
  return xx;
}

int main(){
    int    k  = in_nextInt();
    double w  = in_nextDouble()/2.;
    double l  = in_nextDouble();
    double l2 = l / ( (4<<k) - 3 - (1<<k));
    printf("%.7lf\n", atan(l2 / w) * 180. / M_PI);
    return 0;
}
