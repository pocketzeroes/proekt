#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int*g;
int*used;

int ans = 0;

void clean(int v){
  used[v] = 1;
  if (!used[g[v]]){
    clean(g[v]);
    printf("%d %d\n", v + 1, g[v] + 1);
  }
}
int main(){
  int n;
  scanf("%d", &n);
  g=calloc(n, sizeof(int));
  int cnt[n];memset(cnt,0,sizeof(cnt));
  used=calloc(n, sizeof(int));
  for (int i = 0; i < n; ++i){
    int u;
    scanf("%d", &u);
    u--;
    g[i] = u;
    cnt[u]++;
  }
  for (int i = 0; i < n; ++i)
    if (cnt[i] == 0)
      clean(i);
  for (int i = 0; i < n; ++i)
    if (!used[i])
      clean(i);
  printf("%d", ans);
  return 0;
}
