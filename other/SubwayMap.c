#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define swap(a,b) do{ __typeof(a) tp; tp = a; a = b; b = tp; }while(0)
typedef long long ll;
typedef struct{
  ll first, second;
}pll;
pll newpll(int a, int b){
  return(pll){a,b};
}

///////////////////////////////////
typedef struct{
    ll a, b, weight;
    bool unknown, inMST;
}Edge;

typedef struct{
  ll   first;
  Edge*second;
}ple;
ple newple(int a, Edge*b){
  return(ple){a,b};
}

#define pbe(zpv, zvv) zpv.ptr = pushbackE(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
ple*pushbackE(ple*array, int *size, ple value){
  ple*output = resizeArray(array, ple, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	ple*ptr;
	int sz;
}vece;
vece newVecE(){
	vece rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

typedef struct{
    vece edges; //of ple . ple={ll, edge*}
    ll   depth; // = 0ll
}Node;
Node*nodes;
Edge*edges;
enum{MAX_LOG2_N = 18};
pll lift[100001][MAX_LOG2_N];


void mstDFS(ll i, ll p){
    for(int z=0; z<nodes[i].edges.sz; z++){ple e = nodes[i].edges.ptr[z];
        if(e.second->inMST && e.first != p){
            nodes[e.first].depth = nodes[i].depth + 1;
            lift[e.first][0] = newpll(i, e.second->weight);
            mstDFS(e.first, i);
        }
    }
}
int main(){
    ll n, m;
    scanf("%lld %lld", &n, &m);
    nodes = calloc(n, sizeof(Node));
    edges = calloc(m, sizeof(Edge));
    for(ll i=0; i<m; i++){
        char weight[32];
        scanf("%lld %lld %s %lld ", &edges[i].a, &edges[i].b, &weight, &edges[i].inMST);
        edges[i].a--, edges[i].b--;
        pbe(nodes[edges[i].a].edges, newple(edges[i].b, &edges[i]));
        pbe(nodes[edges[i].b].edges, newple(edges[i].a, &edges[i]));
        edges[i].unknown = (weight[0] == '?');
        if(edges[i].unknown)
           edges[i].weight = edges[i].inMST;
        else
           edges[i].weight = atoll(weight);
    }
    mstDFS(0, -1);
    for(ll d=1; d<MAX_LOG2_N; d++){
        for(ll i=0; i<n; i++){
            ll midNode = lift[i][d - 1].first;
            lift[i][d] = newpll(lift[midNode][d - 1].first, fmaxl(lift[i][d - 1].second, lift[midNode][d - 1].second));
        }
    }
    for(int z=0;z<m;z++){Edge e=edges[z];
        if(!e.unknown)
            continue;
        ll w = e.weight;
        if(!e.inMST){
            ll u = e.a,
               v = e.b;
            if(nodes[u].depth < nodes[v].depth)
                swap(u, v);
            for(ll d = MAX_LOG2_N - 1; d >= 0; d--){
                if(nodes[u].depth - (1LL << d) >= nodes[v].depth){
                    w = fmaxl(w, lift[u][d].second);
                    u = lift[u][d].first;
                }
            }
            if(u != v){
                for(ll d = MAX_LOG2_N - 1; d >= 0; d--){
                    if(lift[u][d].first != lift[v][d].first){
                        w = fmaxl(w, fmaxl(lift[u][d].second, lift[v][d].second));
                        u = lift[u][d].first;
                        v = lift[v][d].first;
                    }
                }
                w = fmaxl(w, fmaxl(lift[u][0].second, lift[v][0].second));
            }
        }
        printf("%lld\n", w);
    }
    return 0;
}
