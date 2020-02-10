#pragma GCC optimize "-O3" /* https://vjudge.net/problem/UVA-10989 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
int**newmat(int x, int y){
  int i;
  int**rv = calloc(x, sizeof(int*));
  for(i=0; i<x; i++)
    rv[i] = calloc(y, sizeof(int));
  return rv;
}
enum{ INF = 1000000000};
int wsz;

int GetMinCut(int**weights){
  int N = wsz;
  int*used = calloc(N, sizeof(int));
/* vec cut, best_cut; */
  int best_weight=-1;
  int phase, i, j;
  for(phase=N-1; phase>=0; phase--){
    int*w     = calloc(N, sizeof(int)); memcpy(w, weights[0], N*sizeof(int));
    int*added = calloc(N, sizeof(int)); memcpy(added, used, N*sizeof(int));
    int prev, last = 0;
    for(i=0; i<phase; i++){
      prev = last;
      last = -1;
      for(j=1; j<N; j++)
        if(!added[j] && (last == -1 || w[j] > w[last]))
          last = j;
      if(i == phase-1){
        for(j=0; j<N; j++)
          weights[prev][j] += weights[last][j];
        for(j=0; j<N; j++)
          weights[j][prev] = weights[prev][j];
        used[last] = true;
/*      pb(cut, last); */
        if(best_weight == -1 || w[last] < best_weight){
/*        best_cut = cut; */
          best_weight = w[last];
        }
      }
      else{
        for(j=0; j<N; j++)
          w[j] += weights[last][j];
        added[last] = true;
      }
    }
  }
  return best_weight;/* best_cut); */
}
int main(){
  int N,i,j,n,m,a,b,c;
  scanf("%d", &N);
  for(i=0; i<N; i++){
    scanf("%d %d", &n, &m);
    int**weights = newmat(n, n); wsz = n;
/*  int weights[n][n]; clr(weights); wsz = n; */
    for(j=0; j<m; j++){
      scanf("%d %d %d", &a, &b, &c);
      weights[a-1][b-1] = weights[b-1][a-1] = c;
    }
    int res = GetMinCut(weights);
    printf("Case #%d: %d\n", i+1, res);
  }
  return 0;
}
