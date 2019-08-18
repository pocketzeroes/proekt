#include<stdio.h>
#include<string.h>
#include<stdbool.h>
enum{ maxn = 1010};
int t, n, m, k;
int idx(char*s){
  int x;
  if(sscanf(s + 2, "%d", &x) == EOF)
    return -1;
  if(strncmp(s, "AP", 2) == 0)
    return x;
  if(strncmp(s, "AS", 2) == 0)
    return x + n;
  if(strncmp(s, "BP", 2) == 0)
    return x + n + k;
  if(strncmp(s, "BS", 2) == 0)
    return x + n + k + m;
  return -1;
}
char out[10];
void idxi(int x){
  if(x <= 0)
    sprintf(out, "error! index < 0!");
  else if(x <= n)
    sprintf(out, "AP%d", x);
  else if(x <= n + k)
    sprintf(out, "AS%d", x - n);
  else if(x <= n + k + m)
    sprintf(out, "BP%d", x - n - k);
  else if(x <= n + k + m + k)
    sprintf(out, "BS%d", x - n - k - m);
  else
    sprintf(out, "error! index > n + k + m + k");
}
typedef struct Edge{
  int nxt, v, f;
}Edge;
Edge e[maxn << 4];
int tot, pre[maxn << 2], ans, que[maxn << 2];
bool leaf[maxn << 2], vis[maxn << 2];
void addedge(int u, int v){
  e[tot] = (Edge){pre[u], v, 0};
  pre[u] = tot++;
  e[tot] = (Edge){pre[v], u, 0};
  pre[v] = tot++;
}
bool dfs(int u, int p){
  int cnt = 0;
  for(int it = pre[u]; it != -1; it = e[it].nxt){
    if(it == (p ^ 1))
      continue;
#define v e[it].v
    if(!dfs(v, it))
      return 0;
    cnt += !e[it].f;
  }
  if(cnt == 2 && p != -1)
    e[p].f = e[p ^ 1].f = 1;
  return leaf[u] || cnt == 1 || cnt == 2;
}
bool pfs(int u){
  vis[u] = 1;
  que[ans++] = u;
  int cnt = 0;
  for(int it = pre[u]; it != -1; it = e[it].nxt){
    if(e[it].f)
      continue;
    ++cnt;
    if(!vis[v] && !pfs(v))
      return 0;
  }
  return cnt == 2;
  #undef v
}
int main(){
  char x[10], y[10];
  scanf("%d", &t);
  while(t--){
    bool flag = 1;
    tot = ans = 0;
    memset(vis, 0, sizeof vis);
    memset(pre, -1, sizeof pre);
    memset(leaf, 0, sizeof leaf);
    scanf("%d%d%d", &k, &n, &m);
    for(int i = 1; i <= k; ++i)
      leaf[n + i] = leaf[n + k + m + i] = 1;
    for(int i = 1; i < n + k; ++i){
      scanf("%s%s", x, y);
      addedge(idx(x), idx(y));
    }
    flag &= dfs(1, -1);
    for(int i = 1; i < m + k; ++i){
      scanf("%s%s", x, y);
      addedge(idx(x), idx(y));
    }
    if(flag)
      flag &= dfs(n + k + 1, -1);
    for(int i = 0; i < k; ++i){
      scanf("%s%s", x, y);
      addedge(idx(x), idx(y));
    }
    if(flag)
      flag &= pfs(1);
    if(flag && ans == n + k + m + k){
      printf("YES");
      for(int i = 0; i < ans; ++i){
        idxi(que[i]);
        printf(" %s", out);
      }
      putchar('\n');
    }
    else
      puts("NO");
  }
  return 0;
}
