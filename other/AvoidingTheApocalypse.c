#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define pbe(zpv, zvv) zpv.ptr = pushbackE(zpv.ptr, &zpv.sz, zvv)
#define pb(zpv, zvv) zpv.ptr = pushbackL(zpv.ptr, &zpv.sz, zvv)
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
const ll inf = (ll)1 << 60;
enum{MAXN = 1000010};

typedef struct{
  ll a, b, cap, flow;
}edge;
edge*pushbackE(edge*array, int *size, edge value){
  edge*output = resizeArray(array, edge, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	edge*ptr;
	int sz;
}vece;
vece newVecE(){
	vece rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

ll n, s, t, d[MAXN], ptr[MAXN], q[MAXN];
vece e;
vecl g[MAXN];
typedef struct{
  ll a, b, cap, t;
}road;

void addedge(ll a, ll b, ll cap){
  edge e1 = { a, b, cap, 0 };
  edge e2 = { b, a, 0, 0 };
  pb(g[a], e.sz);
  pbe(e, e1);
  pb(g[b], e.sz);
  pbe(e, e2);
}
bool bfs(){
  ll qh=0, qt=0;
  q[qt++] = s;
  memset(d, -1, n * sizeof d[0]);
  d[s] = 0;
  while(qh < qt && d[t] == -1) {
    ll v = q[qh++];
    for(size_t i=0; i<g[v].sz; ++i) {
      ll id = g[v].ptr[i],
         to = e.ptr[id].b;
      if(d[to] == -1 && e.ptr[id].flow < e.ptr[id].cap) {
        q[qt++] = to;
        d[to] = d[v] + 1;
      }
    }
  }
  return d[t] != -1;
}
ll dfs(ll v, ll flow) {
  if(!flow) return 0;
  if(v == t) return flow;
  for(; ptr[v]<(ll)g[v].sz; ++ptr[v]) {
    ll id = g[v].ptr[ptr[v]];
        ll to = e.ptr[id].b;
    if(d[to] != d[v] + 1)  continue;
    ll pushed = dfs(to, fmin(flow, e.ptr[id].cap - e.ptr[id].flow));
    if(pushed) {
      e.ptr[id].flow += pushed;
      e.ptr[id^1].flow -= pushed;
      return pushed;
    }
  }
  return 0;
}
ll getflow() {
  ll flow = 0;
  for(;;) {
    if(!bfs())  break;
    memset(ptr, 0, n * sizeof ptr[0]);
    ll pushed;
    while(pushed = dfs(s,inf))
      flow += pushed;
  }
  return flow;
}
void reset() {
  e.sz=0;
  for(int i = 0; i < n; i++)
    g[i].sz=0;
}
void solve(){
  ll locations, start, group, time;
  scanf("%lld%lld%lld%lld", &locations, &start, &group, &time);
  start--;
  time++;
  ll ends;
  scanf("%lld", &ends);
  ll loc[ends];
  for(int z=0;z<ends;z++){
    scanf("%lld", &loc[z]);
    loc[z]--;
  }
  ll r;
  scanf("%lld", &r);
  road roads[r];
  for(int z=0;z<r;z++){
    scanf("%lld%lld%lld%lld", &roads[z].a, &roads[z].b, &roads[z].cap, &roads[z].t);
    roads[z].a--;
    roads[z].b--;
  }
  n = locations * time + 2;
  s = n-1;
  t = n-2;
  addedge(s, start, group);
  for(int i = 1; i < time; i++){
    ll t1 = (i-1) * locations;
    ll t2 = i * locations;
    for(int j = 0; j < locations; j++)
      addedge(t1+j, t2+j, inf);
  }
  for(int z=0;z<r;z++){
#define i roads[z]
    for(ll j = 0; j < time; j++){
      if(j + i.t >= time) 
        break;
      ll t1 = j;
      ll t2 = j + i.t;
      ll n1 = t1*locations + i.a;
      ll n2 = t2*locations + i.b;
      addedge(n1, n2, i.cap);
    }
  }
#undef i
  for(int z=0; z<ends; z++){ll i = loc[z];
    for(ll j = 0; j < time; j++){
      ll n1 = j * locations + i;
      addedge(n1, t, inf);
    }
  }
  printf("%lld\n", getflow() );
  reset();
}
int main(){
  ll cases;
  scanf("%lld", &cases);
  while(cases--)
    solve();
  return 0;
}
