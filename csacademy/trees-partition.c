#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}


int n, m, x, y, z, k, w;
int iLink[600005], ed[600005], l[300005];
int tree_pos[300005], siz[300005], siz2[300005], pre_order[300005];
int ans;
int iMin[300050], iMax[300050];


void bd(int x, int y){
  iLink[w] = l[x];
  l[x] = w;
  ed[w++] = y;
}
void DFS(int x, int y){
  siz[x] = 1;
  tree_pos[x] = ++k;
  pre_order[k] = x;
  for (int i = l[x]; i != -1; i = iLink[i]){
    if (ed[i] == y)
      continue;
    DFS(ed[i], x);
    siz[x] += siz[ed[i]];
  }
}
void solve(int x, int y){
  iMin[x] = iMax[x] = tree_pos[x];
  siz2[x] = 1;
  for (int i = l[x]; i != -1; i = iLink[i]){
   if (ed[i] == y) 
     continue;
   solve(ed[i], x);
   siz2[x] += siz2[ed[i]];
   iMin[x] = min(iMin[x], iMin[ed[i]]);
   iMax[x] = max(iMax[x], iMax[ed[i]]);
  }
  if (iMax[x] - iMin[x] + 1 == siz2[x] && siz[pre_order[iMin[x]]] == siz2[x])
    ans++;
}
int main (){
  scanf("%d", &n);
  for(int i = (1); i <= (n); i++)
    l[i] = -1;
  for(int i = (2); i <= (n); i++)
    scanf("%d", &x), bd(x, i), bd(i, x);
  DFS(1, 0);
  for(int i = (1); i <= (n); i++)
    l[i] = -1;
  w = 0;
  for(int i = (2); i <= (n); i++)
    scanf("%d", &x), bd(x, i), bd(i, x);
  solve(1, 0);
  printf("%d\n", ans - 1);
  return 0;
}
