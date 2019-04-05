#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
double max(double a, double b){return a>b?a:b;}

int main(){
  int p, a, b, c, d, n;
  while(scanf("%d %d %d %d %d %d", &p, &a, &b, &c, &d, &n)==6){
    double v[n+1];
    for(int i = 1; i <= n; i++){
      v[i] = p*(sin(a*(double)i + b) + cos(c*(double)i + d) + 2);
    }
    double mx = v[1], ret = 0.0;
    for(int i = 1; i <= n; i++){
      if(v[i] > mx)
        mx = v[i];
      else
        ret = max(ret, mx-v[i]);
    }
    printf("%.6lf\n", ret);
  }
  return 0;
}
