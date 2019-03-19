#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int max(int a,int b){return a>b?a:b;}
double sqr(double x) { return x*x; }

int main(){
  int T;
  double c, d, x;
  scanf("%d %lf %lf", &T, &c, &d);
  x = 3600*c*sqr(d);
  int r   [T  ]; 
  int rsum[T+1]; memset(rsum, 0, sizeof(rsum));
  for(int i=0; i<T; i++){
    scanf("%d", &r[i]);
    rsum[i+1] = rsum[i] + r[i];
  }
  double best = 1E99;
  for(int a=0; a<T; a++){
    for(int b=a; b<T; b++){
      int m = max(r[a], r[b]);
      double t = sqrt(x/m);
      if ( t<(b-a) || t>(b-a+1) )
        t = b-a+1;
      double curr = x/t + rsum[b+1]-rsum[a] - m*(b-a+1-t);
      if ( curr < best )
        best = curr;
    }
  }
  printf("%.10lf\n", best);
  return 0;
}
