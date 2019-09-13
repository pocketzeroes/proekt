#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#include<stdint.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)

typedef long long ll;
#define inf (1ll<<60)
void fill(ll*arr, int sz, ll val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}

typedef struct{
    ll a, b, cap, cost, flow;
    size_t back;
}Edge;
#define pb(zpv, zvv) zpv.ptr = pushbackE(zpv.ptr, &zpv.sz, zvv)
#define pbl(zpv, zvv) zpv.ptr = pushbackL(zpv.ptr, &zpv.sz, zvv)
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

//////////////////////////////
vece e;
vecl*g;
ll n, s, t;
ll k = inf;

void mincostmaxflow(ll _n, ll _s, ll _t){
    n=_n;
    s=_s;
    t=_t;
    g = calloc(n, sizeof(vecl));
}
void addedge(ll a, ll b, ll cap, ll cost){
    Edge e1 =(Edge){a,b,cap,cost,0,g[b].sz};
    Edge e2 =(Edge){b,a,0,-cost,0,g[a].sz};
    pbl(g[a], e.sz);
    pb(e, e1);
    pbl(g[b], e.sz);
    pb(e, e2);
}
ll getflow(){
    ll flow = 0, cost = 0;
    while(flow < k){
        ll id[n]; clr(id);
        ll d [n]; fill(d, n, inf);
        ll q [n]; clr(q);
        ll p [n]; clr(p);
        size_t p_edge[n]; clr(p_edge);
        ll qh=0, qt=0;
        q[qt++] = s;
        d[s] = 0;
        while(qh != qt) {
            ll v = q[qh++];
            id[v] = 2;
            if(qh == n) qh = 0;
            for(size_t i=0; i<g[v].sz; ++i){
        #define r e.ptr[g[v].ptr[i]]
                if(r.flow < r.cap && d[v] + r.cost < d[r.b]) {
                    d[r.b] = d[v] + r.cost;
                    if(id[r.b] == 0) {
                        q[qt++] = r.b;
                        if(qt == n) 
                            qt = 0;
                    }
                    else if(id[r.b] == 2) {
                        if(--qh == -1) 
                            qh = n-1;
                        q[qh] = r.b;
                    }
                    id[r.b] = 1;
                    p[r.b] = v;
                    p_edge[r.b] = i;
                }
            }
        #undef r
        }
        if(d[t] == inf) 
            break;
        ll addflow = k - flow;
        for(ll v=t; v!=s; v=p[v]) {
            ll pv = p[v]; 
            size_t pr = p_edge[v];
            addflow = fminl(addflow, e.ptr[g[pv].ptr[pr]].cap - e.ptr[g[pv].ptr[pr]].flow);
        }
        for(ll v=t; v!=s; v=p[v]) {
            ll pv = p[v]; 
            size_t pr = p_edge[v],
                   r = e.ptr[g[pv].ptr[pr]].back;
            e.ptr[g[pv].ptr[pr]].flow += addflow;
            e.ptr[g[v ].ptr[r ]].flow -= addflow;
            cost += e.ptr[g[pv].ptr[pr]].cost * addflow;
        }
        flow += addflow;
    }

    return cost;
}
ll getweight(ll year, ll choice){
    return year * 4 - choice;
}
void solve(ll n, ll m) {
    ll N = n+m+2;
    ll S = N-1;
    ll T = N-2;
    mincostmaxflow(N, S, T);
    for(ll i = 0; i < n; i++){
        ll t;
        scanf("%lld", &t);
        addedge(m+i, T, t, 0);
    }
    for(ll i = 0; i < m; i++){
        ll year;
        scanf("%lld", &year);
        ll job[4];
        for(int z=0;z<4;z++){
            scanf("%lld", &job[z]);
        }
        addedge(S, i, 1, 0);
        for(ll j = 0; j < 4; j++)
            addedge(i, m+job[j], 1, -getweight(year,j));
    }
    ll rv = getflow();
    printf("%lld\n", -rv);
}
int main() {
    ll n, m;
    while(scanf("%lld %lld", &n, &m)==2){
        if(n == 0 && m == 0)
            break;
        else
            solve(n,m);
    }
    return 0;
}
