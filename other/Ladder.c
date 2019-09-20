#include<stdio.h>
#include<math.h>

int main(){
  int h, v;
  scanf("%d%d", &h, &v);
  printf("%.0lf\n", ceil(h / sin(v*M_PI/180.)));
  return 0;
}
