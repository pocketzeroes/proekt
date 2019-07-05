#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int in_nextInt(){
  int x;
  scanf("%d", &x);
  return x;
}

inline double z(int a, int b){
  return a/(double)(a + b);
}
int main(){
  int k = in_nextInt();
  int t = in_nextInt();
  int p = in_nextInt();
  int q = in_nextInt();
  int x[t]; memset(x, 0, sizeof(x));
  x[0] = in_nextInt();
  for (int i = 1; i < t; i++)
    x[i] = (x[i-1] * p) % q;
  for (int i = 0; i < t; i++)
    x[i] %= 4;
  int w[t][4]; memset(w, 0, sizeof(w));
  for (int i = 0; i < t; i++)
    for (int j = 0; j < 4; j++)
      w[i][j] = in_nextInt();
  double prob[t+1][t+1]; memset(prob,0,sizeof(prob));
  prob[0][0] = 1.0;
  for (int i = 0; i < t; i++){
    int predictedWinner = x[i];
    int a = w[i][x[i]];
    int b = w[i][x[i]^1];
    int c = w[i][x[i]^2];
    int d = w[i][x[i]^3];
    double probabilityOfSuccess = z(a, b) * (z(c, d) * z(a, c) + z(d, c) * z(a, d));
    double probabilityOfFailure = 1.0 - probabilityOfSuccess;
    for (int j = 0; j <= i; j++){
      prob[j+1][i+1] += probabilityOfSuccess * prob[j][i];
      prob[j  ][i+1] += probabilityOfFailure * prob[j][i];
    }
  }
  double total = 0.;
  for(int i = k; i <= t; i++)
    total += prob[i][t];
  printf("%.10lf\n", total);
  return 0;
}
