#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}
int cmp(const void * a, const void * b){
  return ( *(int*)a - *(int*)b );
}


// task F == gondola
int N, T, G;
int X    [500];
int cost1[500][500];

int Cost1(int i0, int i1){
  i0 %= N;
  if ((i1 - i0 + N) % N == 1)
    return 0;
#define ret cost1[i0 % N][i1 % N]
  if(!ret)
    ret = 1 + Cost1(i0+1, i1) + (X[i1] - X[(i0+1)%N] + T) % T;
  return ret - 1;
}
int cost[9][500][500],
    tcost[500][500],
    ncost[500][500];
int idx[500], NN = 0;

int solve(){
  if (G >= NN)
    return 0;
  int ans = 1<<20;
  for (int i = 0; i < NN; ++i)
    for (int j = 0; j < NN; ++j)
      cost[0][i][j] = Cost1(idx[i], idx[j]);
  for (int b = 1; (1<<b) <= G; ++b) {
    for (int i = 0; i < NN; ++i)
      for (int j = 0; j < NN; ++j) {
        int v = cost[b-1][i][j];
        for (int k = 1; (i+k) % NN != j; ++k)
          v = min(v, cost[b-1][i][(i+k)%NN] + cost[b-1][(i+k)%NN][j]);
          cost[b][i][j] = v;
      }
  }
  for (int i = 0; i < NN; ++i)
    for (int j = 0; j < NN; ++j)
      tcost[i][j] = 1<<20;
  for (int b = 0; (1<<b) <= G; ++b) {
    if (G & (1<<b)) {
      for (int i = 0; i < NN; ++i)
        for (int j = 0; j < NN; ++j){
          int v = min(cost[b][i][j], tcost[i][j]);
          for (int k = 1; (i+k) % NN != j; ++k)
            v = min(v, cost[b][i][(i+k)%NN] + tcost[(i+k)%NN][j]);
          ncost[i][j] = v;
        }
      memcpy(tcost, ncost, sizeof(tcost));
    }
  }
  for (int i = 0; i < NN; ++i)
    ans = min(ans, tcost[i][i]);
  return ans;
}
int main(){
  scanf("%d %d %d", &N, &T, &G);
  T *= 2;
  for (int i = 0; i < N; ++i)
    scanf("%d", X+i), X[i] %= T;
  qsort(X, N, sizeof(int), cmp);
  NN = 0;
  for (int i = 0; i < N; ++i)
    if (i == N-1 || X[i] != X[i+1])
      idx[NN++] = i;
  printf("%d\n", solve());
  return 0;
}
