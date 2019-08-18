#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
typedef long long ll;
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
ll*pushbackL(ll*array, int*size, ll value){
  ll*output = resizeArray(array, ll, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
  ll*ptr;
  int sz;
}vecl;
vecl newVecL(){
  vecl rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}
void dfs(int u, vecl*E, ll*addsub, ll*subsub, ll*vlof, ll*col, bool*cross){
  col[u] = 1LL;
  for(int i=0;i<E[u].sz;i++){int v = E[u].ptr[i];
    if(col[v] == 0LL){
      dfs(v, E, addsub, subsub, vlof, col, cross);
      addsub[u] += addsub[v];
    } 
    else if(col[v] == 1LL){
      addsub[u]++;
      subsub[v]++;
    }
    else if(col[v] == 2LL)
     *cross = true;
  }
  addsub[u] -= subsub[u];
  vlof  [u] += addsub[u];
  col   [u] = 2LL;
}
void dfs2(int u, vecl*E, ll*r){
  r[u] = 1LL;
  for(int i=0;i<E[u].sz;i++){int v = E[u].ptr[i];
    if (!r[v])
      dfs2(v, E, r);
  }
}
int main(){
  int n, m;
  scanf("%d%d", &n, &m);
  vecl E [n]; clr(E);
  vecl RE[n]; clr(RE);
  while (m--) {
    int u, v;
    scanf("%d%d", &u, &v);
    E [u].ptr=pushbackL(E [u].ptr,&E [u].sz,v);
    RE[v].ptr=pushbackL(RE[v].ptr,&RE[v].sz,u);
  }
  ll addsub[n]; clr(addsub);
  ll subsub[n]; clr(subsub);
  ll color [n]; clr(color );
  ll rch   [n]; clr(rch   );
  ll vlof  [n]; clr(vlof  );
  bool cross = false;
  dfs(0, E, addsub, subsub, vlof, color, &cross);
  dfs2(0, RE, rch);
  bool answer = !cross;
  for(int i = 0; i < n; ++i)
    answer = answer && color[i] == 2LL && rch[i] == 1LL && vlof[i] == (ll)(i != 0);
  puts(answer ? "YES" : "NO");
  return 0;
}
