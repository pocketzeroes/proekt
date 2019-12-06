#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
#define swap(a,b) do{ __typeof(a) tp; tp = a; a = b; b = tp; }while(0)

void fill(double*arr, int sz, double val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
double***newmat(int x, int y, int z){
  double***rv = calloc(x, sizeof(double**));
  for(int q=0; q<z; q++){
    rv[q] = calloc(y, sizeof(double*));
    for(int i=0; i<x; i++){
      rv[q][i] = calloc(y, sizeof(double));
      fill(rv[q][i], z, -1.);
    }
  }
  return rv;
}

int main(){
  int n, m;
  scanf("%d %d", &n, &m);
  double***mat = newmat(n, n, n);
  for(int i=0; i<n; ++i)
    for(int k=0; k<n; ++k)
      mat[i][i][k] = 1;
  for(int i=0; i<m; ++i){
    int u, v;
    double p;
    scanf("%d %d %lf", &u, &v, &p);
    if(u > v)
      swap(u, v);
    mat[u][v][0] = 1.0 - p;
    for(int k=1; k<n; ++k){
      mat[u][v][k] = 1;
      mat[v][u][k] = 1;
    }
  }
  for(int k=0; k<n; ++k){
    bool expanded[n]; clr(expanded);
    for(int i=0; i<n-2; ++i){
      double max_p = -1;
      int    max_j = -1;
      for(int j=1; j<n; ++j){
        if(!expanded[j] && mat[0][j][k] > max_p){
          max_p = mat[0][j][k];
          max_j = j;
        }
      }
      if(max_p < -0.5)
        break;
      expanded[max_j] = true;
      for(int t=1; t<n; ++t){
        if(max_j == t)
          continue;
        for(int j=0; j<=fmin(n-k, 1); ++j){
          if(mat[max_j][t][j] < -0.5)
            continue;
          double new_p = max_p*mat[max_j][t][j];
          mat[0][t][k + j] = fmax(mat[0][t][k + j], new_p);
        }
      }
    }
  }
  double best = -1;
  for(int i=0; i<n; ++i){
    best = fmax(best, mat[0][n - 1][i]);
    printf("%.12f ", best);
  }
  return 0;
}
