#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)

double W, H, S;

double cost(double a, double b, double c){
  double alen = ((a+b)*S + (b-a))/2;
  double blen = ((b+c)*S + (c-b))/2;
  return(alen*alen + blen*blen - b*b*S*S)/2;
}

int main(){
  int N;
  while(scanf("%lf %lf %d", &W, &H, &N)==3){
    S = H/W;
    double v[N+2]; clr(v);
    v[0] = 0;
    v[1] = 1;
    for(int i=2; i<=N+1; i++)
      v[i] = 2/(1-S*S) * v[i-1] - v[i-2];
    for(int i=0; i<=N+1; i++)
      v[i] *= W/v[N+1];
    double ret = cost(0, 0, v[1]) + cost(v[N], W, W);
    for(int i=1; i+1<N+2; i++)
      ret += cost(v[i-1], v[i], v[i+1]);
    printf("%.6lf\n", ret);
    for(int i=1; i+1<N+2&&i<=10; i++){
      if(i>1)
        putchar(' ');
      printf("%.6lf", v[i]);
    }
    putchar('\n');
  }
  return 0;
}
