#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
double min(double a, double b){return a<b?a:b;}
double max(double a, double b){return a>b?a:b;}
void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}

int*vis;
int*match;
double mid;
int N,B,R;
double*x;
double*y;

int aug(int l){
  if(vis[l])
    return 0;
  vis[l] = 1;
  for(int r=B; r<B+R; r++){
    if(sqrt((x[l]-x[r])*(x[l] - x[r]) + (y[l] - y[r])*(y[l]-y[r])) < mid){
      if(match[r] == -1 || aug(match[r])){
        match[r] = l;
        return 1;
      }
    }
  }
  return 0;
}
int main(){
  scanf("%d %d %d", &N, &B, &R);
  x=calloc(B+R, sizeof(double));
  y=calloc(B+R, sizeof(double));
  double lo = 0;
  double hi = 0;
  for(int i=0; i<B+R; i++){
    scanf("%lf %lf", &x[i], &y[i]);
    hi = max(hi, 2*sqrt(x[i]*x[i] + y[i]*y[i]));
  }
  while(hi - lo > .00000001){
    mid = (hi + lo)/2;
    int MCBM = 0;
    match = calloc(B+R, sizeof(int));
    fill(match, B+R, -1);
    for(int l=0; l<B; l++){
      vis = calloc(B+R, sizeof(int));
      MCBM += aug(l);
    }
    if(MCBM + N <= B + R)
      lo = mid;
    else
      hi = mid;
  }
  printf("%.8lf\n", hi);
  return 0;
}
