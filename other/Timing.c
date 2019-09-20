#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#include<float.h>

const double eps = 1e-9;
int numCases, numForts, numLinks, attack, s, t, N;
double p, u[100];
bool conn[100][100];

typedef struct{
  double a[100][100];
}M;
M m;

M matmul(M A, M B){
  M R = {0};
  for (int i = (0); i < (N); i++) 
    for (int j = (0); j < (N); j++) 
      for (int k = (0); k < (N); k++)
        R.a[i][j] = A.a[i][k] * B.a[k][j] + R.a[i][j];
  return R;
}
M mpow(M A, int exp){
  M R = {0};
  for (int i = (0); i < (N); i++)
    R.a[i][i] = 1;
  while (exp) {
    if (exp % 2)
      R = matmul(R, A);
    A = matmul(A, A);
    exp /= 2;
  }
  return R;
}
int main(){
  scanf("%d", &numCases);
  while(numCases-- > 0){
    scanf("%d%d%d", &numForts, &numLinks, &attack);
    N = numForts;
    for(int i = (0); i < (numForts); i++){
      scanf("%lf", &u[i]);
      for(int j = (0); j < (numForts); j++){
        m.a[i][j] = 0.;
        conn[i][j] = false;
      }
      m.a[i][i] = 1.;
    }
    for(int i = (0); i < (numLinks); i++){
      scanf("%d %d %lf", &s, &t, &p);
      assert(m.a[s][t] == 0);
      m.a[s][t] = p;
      m.a[s][s] -= p;
      conn[s][t] = conn[t][s] = true;
      assert(m.a[s][s] >= -eps);
    }
    double res[numForts];
    if (attack > 0){
      m = mpow(m, attack);
      for (int i = (0); i < (numForts); i++){
        res[i] = 0.;
        for (int j = (0); j < (numForts); j++)
          res[i] += m.a[j][i] * u[j];
      }
    }
    else {
      for (int i = (0); i < (numForts); i++)
        res[i] = u[i];
    }
    double best = DBL_MAX;
    for (int i = (0); i < (numForts); i++){
      double tmp = res[i];
      for (int j = (0); j < (numForts); j++)
        if (conn[i][j])
          tmp += res[j];
      best = fmin(best, tmp);
    }
    printf("%.15lf\n", best);
  }
  return 0;
}
