#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

double n, p, s, v;

double f(double c){
  return n * pow(log2(n), c*sqrt(2.0)) / (p*1e9) + (1+1/c) * s / v;
}
int main(){
  scanf("%lf %lf %lf %lf", &n, &p, &s, &v);
  double lo = 0, hi = 1;
  while(f(hi) < f(hi/2)) 
    hi *= 2;
  for(int i=0; i<100; i++){
    double a = (2*lo+hi)/3;
    double b = (lo+2*hi)/3;
    if (f(a) < f(b))
      hi = b;
    else
      lo = a;
  }
  printf("%lf %lf\n", f(lo), lo);    
  return 0;
}
