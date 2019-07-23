#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))

enum{ X = 150};

int main(){
  int runs;
  scanf("%d", &runs);
  while(runs--){
    int n;
    scanf("%d", &n);
    int    x[n]; memset(x,0,sizeof(x));
    double p[n]; memset(p,0,sizeof(p));
    for(int i=0; i<n; i++){
      scanf("%d %lf", &x[i], &p[i]);
      p[i] /= 100.;
    }
    double best[X+1]; memset(best, 0, sizeof(best));
    best[0] = 1;
    for(int i=0; i<n; i++)
      for(int j=X; j>=x[i]; j--)
        best[j] = max(best[j], best[j-x[i]] * p[i]);
    double res = 0;
    for(int i=X/2+1; i<=X; i++)
      res = max(res, best[i]);
    printf("%.10lf\n", 100.*res);
  }
  return 0;
}
