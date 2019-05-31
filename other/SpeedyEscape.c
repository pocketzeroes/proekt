#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
typedef struct{
  int first;
  int second;
}pair;
pair newPair(int a, int b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
pair*pushbackP(pair*array, int *size, pair value){
  pair*output = resizeArray(array, pair, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	pair*ptr;
	int sz;
}vecp;
vecp newVecP(){
	vecp rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

const double inf = 1e50;
int n, m, e;
vecp   adj   [200];
bool   Exit  [200];
double police[200];

void dijkstra(int src, double speed, double*ans, double*death){
  bool used[200];
  for (int i = 0; i < n; ++i)
    ans[i] = inf, used[i] = false;
  ans[src] = 0;
  for (int i = 0; i < n; ++i){
    int a = -1;
    for (int b = 0; b < n; ++b)
      if (!used[b] && (a == -1 || ans[b] < ans[a]))
        a = b;
    if (ans[a] == inf)
      break;
    used[a] = true;
    for(int z=0;z<adj[a].sz;z++){pair it=adj[a].ptr[z];
      double nt = ans[a] + 0.1*it.second / speed;
      if(nt < death[it.first])
        ans[it.first] = min(ans[it.first], nt);
    }
  }
}
bool cando(int src, double speed){
  double t[200];
  dijkstra(src, speed, t, police);
  for (int i = 0; i < n; ++i)
    if (t[i] < inf && Exit[i])
      return true;
  return false;
}
int main(){
  scanf("%d %d %d", &n, &m, &e);
  for (int i = 0; i < m; ++i) {
    int a, b, l;
    scanf("%d %d %d", &a, &b, &l);
    --a, --b;
    adj[a].ptr = pushbackP(adj[a].ptr, &adj[a].sz, newPair(b, l));
    adj[b].ptr = pushbackP(adj[b].ptr, &adj[b].sz, newPair(a, l));
  }
  memset(Exit, 0, sizeof(Exit));
  for (int i = 0; i < e; ++i){
    int E;
    scanf("%d", &E);
    assert(1 <= E && E <= n);
    --E;
    Exit[E] = true;
  }
  int b, p;
  scanf("%d%d", &b, &p);
  assert(1 <= b && b <= n);
  assert(1 <= p && b != p && p <= n);
  --b, --p;
  dijkstra(p, 160, police, police);
  double lo = 0, hi = 1e8;
  for (int i = 0; i < 100; ++i){
    double m = (lo+hi)/2;
    if (cando(b, m))
      hi = m;
    else
      lo = m;
  }
  if (hi == 1e8)
    printf("IMPOSSIBLE\n");
  else
    printf("%.9lf\n", hi);
}
