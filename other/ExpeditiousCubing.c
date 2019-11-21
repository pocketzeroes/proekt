#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define swap(a,b) do{ __typeof(a) tp; tp = a; a = b; b = tp; }while(0)

int main(){
  float a, b, c, d, t;
  scanf("%f %f %f %f %f", &a, &b, &c, &d, &t);
  if(a > b) swap(a, b);
  if(c > d) swap(c, d);
  if(a > c) swap(a, c);
  if(b > d) swap(b, d);
  if     ((a+b+c)/3 > t+1e-3)
    puts("impossible");
  else if((b+c+d)/3 < t+1e-3)
    puts("infinite");
  else
    printf("%.2f", (3*t-b-c) );
  return 0;
}
