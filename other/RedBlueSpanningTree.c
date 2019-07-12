#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
enum{ maxn = 1005  };
enum{ inf = 1 << 30};

typedef struct{
  int u, v;
  char color;
}Edge;
Edge newEdge(int u, int v, char c){
  Edge rez;
  rez.u=u;
  rez.v=v;
  rez.color=c;
  return rez;
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
Edge*pushbackE(Edge*array, int *size, Edge value){
  Edge*output = resizeArray(array, Edge, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	Edge*ptr;
	int sz;
}vece;
vece newVecE(){
	vece rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
  
int par[maxn];
vece reds, blues, mandatoryBlues, G;

int Find(int x){
  while(x != par[x]){
    int*p = &par[x];
   *p = par[*p];
    x = par[*p];
  }
  return x;
}
void Kruskal(int k, vece Edges){
  for(int z=0;z<Edges.sz;z++){Edge e = Edges.ptr[z];
    if(G.sz >= k)
      return;
    int su = Find(e.u);
    int sv = Find(e.v);
    if(su != sv){
      par[su] = par[sv];
      G.ptr = pushbackE(G.ptr, &G.sz, e);
    }
  }
}
int FindSpanningTree(int n, int k){
  for(int i = 0; i < maxn; i++)
    par[i] = i;
  Kruskal(inf, reds);
  Kruskal(inf, blues);
  for(int z=0;z<G.sz;z++){Edge e = G.ptr[z];
    if(e.color == 'B')
      mandatoryBlues.ptr = pushbackE(mandatoryBlues.ptr, &mandatoryBlues.sz, e);
  }
  G.sz=0;
  for(int i=0; i<maxn; i++)
    par[i] = i;
  Kruskal(inf, mandatoryBlues);
  Kruskal(k, blues);
  int blueEdges = G.sz;
  Kruskal(inf, reds);
  if (G.sz == n - 1 && blueEdges == k)
    return 1;
  return 0;
}
int main(){
  int n, m, k;
  scanf("%d %d %d", &n, &m, &k);
  while(m--){
    getchar();
    char color;
    int u, v;
    scanf("%c %d %d", &color, &u, &v);
    if(color == 'R')
      reds.ptr = pushbackE(reds.ptr, &reds.sz, newEdge(u, v, color));
    else
      blues.ptr = pushbackE(blues.ptr, &blues.sz, newEdge(u, v, color));
  }
  int ans = FindSpanningTree(n, k);
  printf("%d\n", ans);
  return 0;
}
