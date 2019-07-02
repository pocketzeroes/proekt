#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
double max(double a, double b){return a>b?a:b;}

int    B[16];
double P[16];
double Prob[17][1<<16];

double prob (int n, int toconvert, int moneyleft, int approached){
  if(toconvert == 0)
    return 1.0;
  if(Prob[toconvert][approached] >= 0)
    return Prob[toconvert][approached];
  int i;
  double best = 0, p;
  for(i = 0; i < n; i++)
    if(!(approached & (1<<i)) && B[i] <= moneyleft){
      p = P[i] * prob(n, toconvert-1, moneyleft - B[i], approached | (1<<i)) + (1-P[i]) * prob(n, toconvert, moneyleft - B[i], approached | (1<<i)); 
      best = max(best, p);
    }
  return Prob[toconvert][approached] = best;
}
int main(){
  int cases, casenr, n, c, m, i, p, j;
  scanf("%d\n", &cases);
  for(casenr = 1; casenr <= cases; casenr++){ 
    scanf("%d %d %d\n", &n, &c, &m);
    for(i = 0; i < n; i++){
      scanf("%d %d\n", &B[i], &p);
      P[i] = p / 100.0;
    }
    for(i = 0; i <= n; i++)
      for(j = 0; j < (1<<n); j++)
        Prob[i][j] = -1;
    printf("%lf\n", prob(n, c, m, 0));
  }
  return 0;
}
