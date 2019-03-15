#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ maxn = 1000};
int mat[2][maxn][maxn];
int n;

int*mult(int mi, int*x){
  int*ret = calloc(n, sizeof(int));
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      ret[i] += mat[mi][i][j] * x[j];
  return ret;
}
int main(){
  while(scanf("%i", &n), n) {
    for(int nm = 0; nm < 2; ++nm)
      for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
          scanf("%i", &mat[nm][i][j]);
    int v[n];
    for(int i = 0; i < n; ++i)
      v[i] = rand();
    int* Av  = mult(0,  v);
    int* A2v = mult(0, Av);
    int* Bv  = mult(1,  v);
    bool equal = true;
    for(int i = 0; i < n; ++i)
      if(A2v[i] != Bv[i]){
        equal = false;
        break;
      }
    puts(equal ? "YES" : "NO");
  }
  return 0;
}
