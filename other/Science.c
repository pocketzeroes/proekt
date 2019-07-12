#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
char buff[1000000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}

enum{ MAXN = 80};

int N;
int F[MAXN+1][MAXN+1];
int C[MAXN+1][MAXN+1];
int SAVEF[MAXN+1][MAXN+1];
bool vis[MAXN+1][2];


bool dfs(int x, bool s){
  if(x == N && !s)
    return true;
  if(vis[x][s])
    return false;
  vis[x][s] = true;
  for(int i = 0; i <= N; i++) {
    if(s ? F[i][x] : C[x][i] - F[x][i]){
      if(dfs(i, !s)) {
        s ? --F[i][x] : ++F[x][i];
        return true;
      }
    }
  }
  return false;
}
int main(){
  for(scanf("%d", &N); ; scanf("%d", &N)){
    if(!N)
      break;
    memset(F, 0, sizeof(F));
    memset(C, 0, sizeof(C));
    for(int i = 0; i < N; i++) {
      char*S=getstr();
      for(int j = 0; j < N; j++)
        C[i][j] = S[j] == 'Y';
    }
    int res;
    for(res = 0; ; res++){
      memcpy(SAVEF, F, sizeof(SAVEF));
      for(int j = 0; j < N; j++){
        F[j][N]++; C[j][N]++;
        F[N][j]++; C[N][j]++;
      }
      bool ok = true;
      for(int j = 0; ok && j < N; j++){
        memset(vis, 0, sizeof(vis));
        ok &= dfs(N, true);
      }
      if(!ok){
        memcpy(F, SAVEF, sizeof(SAVEF));
        break;
      }
    }
    memcpy(C, F, sizeof(F));
    memset(F, 0, sizeof(F));
    printf("%d\n", res);
    for(int i = 0; i < res; i++){
      for(int i = 0; i < N; i++){
        F[N][i] = C[N][i] = 1;
        F[i][N] = C[i][N] = 1;
      }
      for(int j = 0; j < N; j++){
        memset(vis, 0, sizeof(vis));
        dfs(N, true);
      }
      for(int k = 0; k < N; k++){
        for(int j = 0; j < N; j++){
          if(F[j][k]){
            if(k)
              printf(" ");
            printf("%d", j + 1);
            F[j][k] = C[j][k] = 0;
          }
        }
      }
      puts("");
    }
    break;
  }
  return 0;
}
