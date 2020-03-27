#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;

typedef struct{
    ll a, b, cap, flow;
}edge;

#define pbe(zpv, zvv) zpv.ptr = pushbackE(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
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

#define pbl(zpv, zvv) zpv.ptr = pushbackL(zpv.ptr, &zpv.sz, zvv)
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
///////////////////////////////////////////////////

const ll inf = (ll)1<<60;
enum{MAXN = 100000+10};


ll n, s, t, d[MAXN], ptr[MAXN], q[MAXN];
vece e;
vecl g[MAXN];

void addedge(ll a, ll b, ll cap){
    edge e1 = { a, b, cap, 0 };
    edge e2 = { b, a, 0, 0 };
    pbl(g[a], (ll)e.sz);
    pbe(e, e1);
    pbl(g[b], (ll)e.sz);
    pbe(e, e2);
}
bool bfs(){
    ll qh=0, 
       qt=0;
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
    for(; ptr[v]<(ll)g[v].sz; ++ptr[v]){
        ll id = g[v].ptr[ptr[v]];
        ll to = e.ptr[id].b;
        if(d[to] != d[v] + 1)
            continue;
        ll pushed = dfs(to, fminl(flow, e.ptr[id].cap - e.ptr[id].flow));
        if(pushed){
            e.ptr[id].flow   += pushed;
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
        ll pushed;
        while(pushed = dfs(s,inf))
            flow += pushed;
    }
    return flow;
}
int main(){
    int m;
    scanf("%lld %d %lld %lld", &n, &m, &s, &t);
    for(int i=0; i<m; i++){
        int u, v, x;
        scanf("%d %d %d", &u, &v, &x);
        addedge(u, v, x);
    }
    int flow = getflow();
    vece keep = newVecE();
    for(int z=0;z<e.sz;z++){edge i = e.ptr[z];
        if(i.flow > 0){
            pbe(keep, i);
        }
    }
    printf("%lld %d %d\n", n, flow, keep.sz);
    for(int z=0;z<keep.sz;z++){edge i = keep.ptr[z];
        printf("%lld %lld %lld\n", i.a, i.b, i.flow);
    }
    return 0;
}
