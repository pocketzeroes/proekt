#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
#include<assert.h>

enum{ MAX_B = 10 };
enum{ MAX_T = 100};
int B, T; 
double f;
double p[MAX_B];
int    s[MAX_B];   
double A[MAX_T][1 << MAX_B][MAX_T];
int    N[MAX_B]; 

double solve(int t, int b, int n){
  if (t == T || b == ((1 << B) - 1)) 
    return 0;
  if (A[t][b][n] == -1){
    int i = -1;
    double m = -1;
    for (int j = 0; j < B; ++j) 
      if (! (b & (1 << j))){
        if (p[j] * s[j] > m) {
          m = p[j] * s[j];
          i = j;
        }
    }
    assert(0 <= i && i <= B);
    double pi = p[i];
    p[i] *= f; ++N[i];
    double x = (1-pi) * solve(t + 1, b, n + 1);
    p[i] = pi; --N[i];
    x += p[i] * (s[i] + solve(t + 1, b | (1 << i), n - N[i]));
    A[t][b][n] = x;
  }
  return A[t][b][n];
}
int main() {
  scanf("%d %d %lf", &B, &T, &f);
  for (int i = 0; i < B; ++i) 
    scanf("%lf %d", &p[i], &s[i]);
  for (int t = 0; t < T; ++t) 
    for (int b = 0; b < 1 << B; ++b) 
      for (int f = 0; f < T; ++f) 
        A[t][b][f] = -1;
  for (int i = 0; i < B; ++i) 
    N[i] = 0;
  printf("%.6lf\n", solve(0,0,0));
}
