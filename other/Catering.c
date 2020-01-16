#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
#define fill(arr, sz, val)do{     \
  for(int i=0; i<sz; i++)         \
    arr[i] = val;                 \
}while(0)

int main(){
  int N, K;
  while(scanf("%d %d", &N, &K)==2){
    int nv = 2*N+3;
    int cap [nv][nv]; clr(cap );
    int cost[nv][nv]; clr(cost);
    for(int i=0; i<=N; i++){
      cap [N+1+i][i] = 1;
      cost[N+1+i][i] = -10000000;
      cost[i][N+1+i] =  10000000;
      cap [i][nv-1 ] = N;
      for(int j = i+1; j <= N; j++){
        cap[i][N+1+j] = 1;
        scanf("%d", &cost[i][N+1+j]);
        cost[N+1+j][i] = -cost[i][N+1+j];
      }
    }
    int ret = 10000000 * N;
    for(int f=0; f<fmin(N, K); f++){
      int best[nv]; fill(best, nv, 1000000000);
      int prev[nv]; fill(prev, nv, -1);
      best[0] = 0;
      bool changed[nv]; fill(changed, nv, true);
      for(int i=0; i<nv; i++){
        bool changed2[nv]; fill(changed2, nv, false);
        for(int j=0; j<nv; j++)
          if(changed[j])
            for(int k=0; k<nv; k++)
              if(cap[j][k]){
                if(best[k] > best[j] + cost[j][k]){
                  best [k] = best[j] + cost[j][k];
                  prev[k] = j;
                  changed2[k] = true;
                }
              }
        memcpy(changed, changed2, sizeof(changed));
      }
      ret += best[nv-1];
      for(int x=nv-1; x!=0; x=prev[x]){
        cap[prev[x]][x]--;
        cap[x][prev[x]]++;
      }
    }
    printf("%d\n", ret);
  }
  return 0;
}
