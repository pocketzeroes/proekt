#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
double min(double a, double b){return a<b?a:b;}
double max(double a, double b){return a>b?a:b;}

int main(){
  double d;
  int n;
  scanf("%lf %d", &d, &n);
  int x, sum = 0;
  double low = 0, 
        high = 1;
  for(int i = 1; scanf("%d", &x)==1; i++){
    sum += x;
    double nlow  = d * i - sum;
    double nhigh = d * i - sum + 1;
    low  = max(low , nlow );
    high = min(high, nhigh);
  }
  puts((low < high) ? "possible" : "impossible");
  return 0;
}
