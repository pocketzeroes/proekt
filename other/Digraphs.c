#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#include<setjmp.h>

static jmp_buf exception_env;
static int exception_type;


int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}
char buff[1000000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}

enum{ N = 26};

bool graph[N][N];
int color[N], dp[N], parent[N];

void dfs(int u, int f){
  if (color[u] == 2)
    return;
  parent[u] = f;
  if (color[u] == 1){ // THROW(u);
    exception_type=u;
    longjmp(exception_env, u);
  }
  color[u] = 1;
  parent[u] = f;
  for (int v = 0; v < N; ++v){
    if (graph[u][v]) {
      dfs(v, u);
      dp[u] = max(dp[u], 1 + dp[v]);
    }
  }
  color[u] = 2;
}
int main(){
  int Z;
  scanf("%d", &Z);
  while (Z--){
    for (int i = 0; i < N; ++i)
      for (int j = 0; j < N; ++j)
        graph[i][j] = true;
    int n;
    scanf("%d", &n);
    while(n--){
      char*w = getstr();
      graph[w[0]-'a'][w[1]-'a'] = false;
    }
    for (int i = 0; i < N; ++i){
      color[i] = 0;
      dp[i] = 0;
    }
    int on_cycle = -1;
    if(!setjmp(exception_env)){
      for (int i = 0; i < N; ++i)
        dfs(i, -1);
    } 
    else{
      on_cycle = exception_type;
    }
    int path[100], path_len = 0;
    if (on_cycle != -1) {
      path_len = 39; 
      for (int i = path_len - 1; i >= 0; --i) {
        path[i] = on_cycle;
        on_cycle = parent[on_cycle];
      }
    }
    else {
      int u = 0;
      for (int i = 0; i < N; ++i)
        if (dp[i] > dp[u]) u = i;
      while (dp[u] > 0) {
        path[path_len++] = u;
        for (int v = 0; v < N; ++v){
          if (graph[u][v] && dp[v] == dp[u] - 1) {
            u = v;
            break;
          }
        }
      }
      path[path_len++] = u;
    }
    path_len = (path_len + 1) / 2;
    for (int i = 0; i < path_len; ++i) {
      for (int j = 0; j < path_len; ++j)
        printf("%c", (char)('a' + path[i + j]));
      puts("");
    }
  }
  return 0;
}
