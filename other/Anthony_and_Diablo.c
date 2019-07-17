#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int main(){
  double a, n;
  scanf("%lf %lf", &a, &n);
  double rad  = n / (2.*M_PI);
  double area = M_PI *(rad*rad);
  if(area >= a)
    puts("Diablo is happy!");
  else
    puts("Need more materials!");
  return 0;
}
