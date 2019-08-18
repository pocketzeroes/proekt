#include<stdio.h>
#include<string.h>
#include<stdbool.h>
typedef long long ll;
#define int ll
enum{ maxn = 20};
int t, n, e[maxn][maxn], c[maxn], ans;
bool vis[1 << maxn];

void dfs(int mask, int size){
  if(vis[mask])
    return;
  vis[mask] = 1;
  if(size == 1){
    ans |= mask;
    return;
  }
  for(int i = 0; i < n; ++i)
    if((mask & (1 << i)) && c[i] > 0){
      for(int j = 0; j < n; ++j)
        c[j] -= e[j][i];
      dfs(mask ^ (1 << i), size - 1);
      for(int j = 0; j < n; ++j)
        c[j] += e[j][i];
    }
}
signed main(){
  scanf("%lld", &t);
  while(t--){
    ans = 0;
    memset(vis, 0, sizeof vis);
    scanf("%lld", &n);
    for(int i = 0; i < n; ++i){
      c[i] = 0;
      for(int j = 0; j < n; ++j){
        scanf("%lld", &e[i][j]);
        c[i] += e[i][j];
      }
    }
    dfs((1 << n) - 1, n);
    if(!ans)
      puts("0");
    else{
      bool flag = 0;
      for(int i = 0; i < n; ++i)
        if(ans & (1 << i)){
          if(flag)
            putchar(' ');
          else
            flag = 1;
          printf("%lld", i + 1);
        }
      putchar('\n');
    }
  }
  return 0;
}
