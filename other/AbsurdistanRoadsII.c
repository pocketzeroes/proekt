#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ MAXN = 150};
double c[MAXN][MAXN];

int main(){
  int n;
  scanf("%d", &n);
  double p[n+1];
  for(int i=0; i<(n+1); ++i){
    c[i][0] = 1;
    for(int j=1; j<(i+1); ++j)
      c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
    p[i] = pow(i - 1, i);
    for(int j=2; j<(i-1); ++j)
      p[i] -= pow(i - j - 1, i - j) * c[i - 1][j - 1] * p[j];
  }
  printf("%.12lf\n", p[n] / pow(n - 1, n));
  return 0;
}
