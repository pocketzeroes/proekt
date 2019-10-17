#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define pb(zpv, zvv) zpv.ptr = pushback(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
  int*ptr;
  int sz;
}vec;
vec newVec() {
  vec rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}
//////////////////////////////////
vec adj    [600];
double dist[600][600];
int st     [600][600];
double ans  [250000];
int mate    [250000];
int par     [250000],
    ht      [250000];
vec children[250000];


int get_head(int i){
  return par[i] == i ? i : get_head(par[i]);
}
bool same(int i, int j){
  return get_head(i) == get_head(j);
}
int join(int i, int j){
  int a = get_head(i),
      b = get_head(j);
  int r = -1;
  if(a != b){
    r = (ht[a] < ht[b]) ? a : b;
    if(ht[a] <= ht[b]){
      par[a] = b;
      pb(children[b], a);
    }
    else{
      par[b] = a;
      pb(children[a], b);
    }
    if(ht[a] == ht[b])
      ++ht[b];
  }
  return r;
}
void search(int r, double d){
  if(r == -1)
    return;
  if(same(r, mate[r]))
    ans[r] = ans[mate[r]] = fmax(d, ans[r]);
  for(int z=0;z<children[r].sz;z++){int c = children[r].ptr[z];
    search(c, d);
  }
}
double sqr(double x){
  return x*x;
}
typedef struct{ // state
  double first;
  int    second;
  int    third;
}state;
state newstate(double a, int b, int c){
  return(state){a,b,c};
}
int cmpS(const void*pa, const void*pb){
  state*a = (state*)pa;
  state*b = (state*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  if(a->third  != b->third )return(a->third  < b->third )?-1:1;
  return 0;
}

#define pbs(zpv, zvv) zpv.ptr = pushbackS(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
state*pushbackS(state*array, int *size, state value){
  state*output = resizeArray(array, state, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	state*ptr;
	int sz;
}vecs;
vecs newVecS(){
	vecs rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}



int main(){
  int n, m;
  scanf("%d", &n);
  int x[600],
      y[600];
  for (int i = 1; i <= n; ++i)
    scanf("%d%d", x+i, y+i);
  for (int i = 1;i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      dist[i][j] = sqrt(sqr(x[i]-x[j])+sqr(y[i]-y[j]));
  scanf("%d", &m);
  for (int i = 0; i < m; ++i){
    int a, b;
    scanf("%d%d", &a, &b);
    pb(adj[a], b);
    pb(adj[b], a);
  }
  vecs S=newVecS();//of state
  for (int i = 1; i <= n; ++i){
    for (int j = 1; j <= n; ++j){
      if (i == j)
        continue;
      pbs(S, newstate(dist[i][j], i, j));
    }
  }
  int N = S.sz;
  qsort(S.ptr, S.sz, sizeof(state), cmpS);
  for(int a = 0; a < N; ++a){
    st[S.ptr[a].second][S.ptr[a].third] = a;
  }
  for(int i = 1; i <= n; ++i){
    for(int j = 1; j <= n; ++j){
      if(i == j)
        continue;
      mate[st[i][j]] = st[j][i];
    }
  }
  for (int i = 0; i < N; ++i)
    par[i] = i, ht[i] = 0;
  for(int at = N-1; at >= 0; --at){
    double d = S.ptr[at].first;
    int u = S.ptr[at].second;
    int v = S.ptr[at].third;
    for(int z=0;z<adj[u].sz;z++){int w = adj[u].ptr[z];
      if(dist[w][v] >= d)
        search(join(at, st[w][v]), d);
    }
    for(int z=0;z<adj[v].sz;z++){int w = adj[v].ptr[z];
      if(dist[u][w] >= d)
        search(join(at, st[u][w]), d);
    }
  }
  int l;
  scanf("%d", &l);
  for(int i=0; i<l; ++i){
    int a, b;
    scanf("%d %d", &a, &b);
    printf("%.9lf\n", ans[st[a][b]]);
  }
  return 0;
}
