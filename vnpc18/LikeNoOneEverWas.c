#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
ll min(ll a, ll b){return a<b?a:b;}

const ll inf = (ll)1 << 60;
enum{ MAXN = 100000 + 10};

typedef struct{
  ll a, b, cap, flow;
}Edge;
Edge newEdge(ll a, ll b, ll c, ll d){
  Edge rez;
  rez.a    = a;
  rez.b    = b;
  rez.cap  = c;
  rez.flow = d;
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

ll n, s, t, d[MAXN], ptr[MAXN], q[MAXN];
vece e;
vecl g[MAXN];

void addedge(ll a, ll b, ll cap){
  Edge e1 = newEdge( a, b, cap, 0);
  Edge e2 = newEdge( b, a,   0, 0);
  g[a].ptr = pushbackL(g[a].ptr, &g[a].sz, e.sz);
  e.ptr = pushbackE(e.ptr, &e.sz, e1);
  g[b].ptr = pushbackL(g[b].ptr, &g[b].sz, e.sz);
  e.ptr = pushbackE(e.ptr, &e.sz, e2);
}
bool bfs(){
  ll qh=0, qt=0;
  q[qt++] = s;
  memset(d, -1, n * sizeof d[0]);
  d[s] = 0;
  while(qh < qt && d[t] == -1){
    ll v = q[qh++];
    for(size_t i=0; i<g[v].sz; ++i){
      ll id = g[v].ptr[i],
         to = e.ptr[id].b;
      if(d[to] == -1 && e.ptr[id].flow < e.ptr[id].cap){
        q[qt++] = to;
        d[to] = d[v] + 1;
      }
    }
  }
  return d[t] != -1;
}
ll dfs(ll v, ll flow){
  if(!flow) 
    return 0;
  if(v == t) 
    return flow;
  for(; ptr[v] < g[v].sz; ++ptr[v]){
    ll id = g[v].ptr[ptr[v]];
    ll to = e.ptr[id].b;
    if(d[to] != d[v] + 1)
      continue;
    ll pushed = dfs(to, min (flow, e.ptr[id].cap - e.ptr[id].flow));
    if(pushed){
      e.ptr[id].flow += pushed;
      e.ptr[id^1].flow -= pushed;
      return pushed;
    }
  }
  return 0;
}
ll getflow(){
  ll flow = 0;
  for(;;){
    if(!bfs())
      break;
    memset(ptr, 0, n * sizeof ptr[0]);
    ll pushed = dfs(s, inf);
    while(pushed){
      flow += pushed;
      pushed = dfs(s, inf);
    }
  }
  return flow;
}
bool isprime(ll n){
  if(n < 2) 
    return false;
  if(n == 2) 
    return true;
  if(n % 2 == 0) 
    return false;
  for(ll i = 3; i*i <= n; i+=2){
    if(n % i == 0){
      return false;
    }
  }
  return true;
}
int main(){
  n = 2 + 10000 + 5000;
  s = 0;
  t = n-1;
  ll n;
  scanf("%lld", &n);
  ll total = 0;
  ll val [n+1]; memset(val, 0, sizeof(val));
  ll cost[n+1]; memset(cost,0,sizeof(cost));
  for(ll i = 1; i <= n; i++){
    scanf("%lld", &val[i]);
    total += val[i];
  }
  for(ll i = 1; i <= n; i++){
    scanf("%lld", &cost[i]);
  }
  for(ll i = 1; i <= n; i++){
    addedge(i, t, val[i]);
  }
  ll node_id = n+1;
  vecl ids[n+1]; memset(ids, 0, sizeof(ids));
  for(ll i = 2; i <= n; i++){
    if(!isprime(i))
      continue;
    ll prevcost = 0;
    ll ct = 0;
    ll t = n;
    while(t > 0){
      ct++;
      ll currcost = ct * ct * cost[i];
      addedge(s,node_id,currcost-prevcost);
      prevcost = currcost;
      ids[i].ptr = pushbackL(ids[i].ptr, &ids[i].sz, node_id);
      node_id++;
      t /= i;
    }
  }
  ll rem[n+1]; memset(rem, 0, sizeof(rem));
  for(ll i = 0; i <= n; i++){
    rem[i] = i;
  }
  for(ll i = 2; i <= n; i++){
    if(!isprime(i))
      continue;
    for(ll j = i; j <= n; j += i){
      ll ct = 0;
      while(rem[j] % i == 0){
        ll node = ids[i].ptr[ct];
        addedge(node, j, inf);
        rem[j] /= i;
        ct++;
      }
    }
  }
  ll flow = getflow();
  printf("%lld\n", total - flow);
  return 0;
}
