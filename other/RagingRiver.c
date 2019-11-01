#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long     ll;
typedef long double   ld;

const char nl  = '\n';
const ll INF   = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD   = 1e9+7;
const ld EPS   = 1e-13;


//namespace Flow{
enum{ N =(int)1e3+4};
enum{ M = N*2};
int par[N], first[N], nxt[2*M], ep[2*M], m;
ll flo[2*M], cap[2*M], cost[2*M];
void init(){
  m = 0;
  memset(first,-1,sizeof first);
  memset(flo,0,sizeof flo);
}
void add_edge(int a, int b, ll c, ll p){
  nxt[m] = first[ep[m]=a], first[ep[m]] = m, cap[m] = c, cost[m] =  p, ++m;
  nxt[m] = first[ep[m]=b], first[ep[m]] = m, cap[m] = 0, cost[m] = -p, ++m;
}
int q[N], inq[N];
#define BUBL { \
t = q[i]; q[i] = q[j]; q[j] = t; \
t = inq[q[i]]; inq[q[i]] = inq[q[j]]; inq[q[j]] = t; }
bool vis[N];
ll pot[N], dist[N];
void mcf_pot_init(int n) {
  memset(pot, 0, sizeof pot);
  for (int k = 1; k < n; ++k)
    for (int e = 0; e < m; ++e)
      if (cap[e])
        pot[ep[e^1]] = fminl(pot[ep[e^1]], pot[ep[e]] + cost[e]);
}
ll mcf_update(int s, int t, ll*price, int n){
  memset(vis, 0, sizeof vis);
  memset(dist, INF, sizeof dist);
  dist[s] = 0;
  memset(inq, -1, sizeof inq);
  int qs = 0;
  inq[q[qs++] = s] = 0;
  while (qs){
    int u = q[0];
    inq[u] = -1;
    q[0] = q[--qs];
    if( qs )
      inq[q[0]] = 0;
    for( int i = 0, j = 2*i + 1, t; j < qs; i = j, j = 2*i + 1 ){
      if( j + 1 < qs && dist[q[j + 1]] < dist[q[j]] )
        j++;
      if( dist[q[j]] >= dist[q[i]] )
        break;
      BUBL;
    }
    if (vis[u] == 1)
      continue;
    vis[u] = 1;
    for (int e = first[u]; e != -1; e = nxt[e]) {
      int v = ep[e^1];
      if (flo[e] < cap[e] && dist[v] > dist[u] + pot[u] - pot[v] + cost[e]){
        dist[v] = dist[u] + pot[u] - pot[v] + cost[e], par[v] = e;
        if( inq[v] < 0 ){
          inq[q[qs] = v] = qs;
          qs++;
        }
        for( int i = inq[v], j = ( i - 1 )/2, t; dist[q[i]] < dist[q[j]]; i = j, j = ( i - 1 )/2 )
          BUBL;
      }
    }
  }
  if (dist[t] >= INF)
    return 0;
  ll df = INF;
  for(int e, i = t; i != s; i = ep[e])
    e = par[i], df = fminl(df, cap[e] - flo[e]);
  for(int e, i = t; i != s; i = ep[e])
    e = par[i], flo[e] += df, flo[e^1] -= df, (*price) += df*cost[e];
  for(int i = 0; i < n; ++i) 
    pot[i] = fminl(INF, dist[i] + pot[i]);
  return df;
}
//}
int main(){
  init();
  int p, n, m;
  scanf("%d %d %d", &p, &n, &m);
  const int s = n+2;
  const int t = n+3;
  for(int i=0; i<m; i++){
    int a, b;
    scanf("%d %d", &a, &b);
    add_edge(a+2,b+2,1,1);
    add_edge(b+2,a+2,1,1);
  }
  add_edge(s, 0, p, 0);
  add_edge(1, t, p, 0);
  mcf_pot_init(n+4);
  ll ans  = 0;
  ll flow = 0;
  ll df;
  while(df = mcf_update(s, t, &ans, n+4))
    flow += df;
  if(flow<p)
    printf("%lld people left behind\n", p-flow);
  else
    printf("%lld\n", ans);
  return 0;
}
