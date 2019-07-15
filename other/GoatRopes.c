#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))


enum{ MAXVAR        =    50};
enum{ MAXCONSTRAINT = 25*49};
#define EPS 1e-7


double C[MAXVAR];
double A[MAXCONSTRAINT][MAXVAR];
double B[MAXCONSTRAINT];
double tableau[MAXCONSTRAINT + 1][MAXVAR + MAXCONSTRAINT + 2];

double simplex(int variables, int constraints){
  int rows = constraints;
  int cols = variables + constraints + 1;
  for(int i = 0; i < constraints; i++) {
    for(int j = 0; j < variables; j++)
      tableau[i][j] = A[i][j];
    for(int j = 0; j < constraints; j++)
      tableau[i][j + variables] = i == j ? 1 : 0;
    tableau[i][variables + constraints] = 0;
    tableau[i][variables + constraints + 1] = B[i];
  }
  for(int j = 0; j < variables; j++)
    tableau[constraints][j] = C[j] == 0 ? 0 : -C[j];
  for(int j = 0; j < constraints; j++)
    tableau[constraints][j + variables] = 0;
  tableau[constraints][variables + constraints] = 1;
  tableau[constraints][variables + constraints + 1] = 0;
  while(1){
    int pivot_col = 0;
    for(int i = 1; i < cols; i++)
      if(tableau[rows][i] < tableau[rows][pivot_col])
        pivot_col = i;
    if(tableau[rows][pivot_col] >= 0)
      break;
    int pivot_row = 0;
    for(int i = 1; i < rows; i++)
      if(tableau[i][pivot_col] >= EPS)
        if(tableau[pivot_row][pivot_col] < EPS || tableau[i][cols] / tableau[i][pivot_col] < tableau[pivot_row][cols] / tableau[pivot_row][pivot_col])
          pivot_row = i;
    for(int i = 0; i <= rows; i++) {
      if(i == pivot_row)
        continue;
      double ratio = tableau[i][pivot_col] / tableau[pivot_row][pivot_col];
      for(int j = 0; j <= cols; j++)
        tableau[i][j] -= ratio * tableau[pivot_row][j];
      tableau[i][pivot_col] = 0;
    }
    for(int i = 0; i <= rows; i++) {
      double mx = 0;
      for(int j = 0; j <= cols; j++) {
        mx = max(mx, fabs(tableau[i][j]));
      }
      for(int j = 0; j <= cols; j++) {
        tableau[i][j] /= mx;
      }
    }
  }
  return tableau[rows][cols] / tableau[rows][cols - 1];
}
double XC[MAXVAR];
double YC[MAXVAR];
int main() {
  for(int t = 1; ; t++) {
    memset(A, 0, sizeof(A));
    memset(B, 0, sizeof(B));
    memset(C, 0, sizeof(C));
    int N;
    scanf("%d", &N);
    if(!N)
      break;
    int p = 0;
    for(int i = 0; i < N; i++) {
      C[i] = 1;
      scanf("%lf%lf", &XC[i], &YC[i]);
      for(int j = 0; j < i; j++){
        A[p][i] = 1;
        A[p][j] = 1;
        B[p++] = sqrt((XC[i] - XC[j]) * (XC[i] - XC[j]) +
                      (YC[i] - YC[j]) * (YC[i] - YC[j]));
      }
    }
    printf("%.2lf\n", simplex(N, p));
    break;
  }
  return 0;
}
