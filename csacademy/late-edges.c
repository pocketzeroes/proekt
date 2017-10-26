#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

typedef long long ll;
ll min(ll a, ll b){return a<b?a:b;}
ll max(ll a, ll b){return a>b?a:b;}

typedef struct Edge_s {
    int a, b;
    ll c;
}Edge;
Edge newEdge(int a, int b, int c){
    Edge rez;
    rez.a=a;
    rez.b=b;
    rez.c=c;
    return rez;
}
void fill(ll*arr,int sz, ll val){
    for(int i=0; i<sz; i++)
        arr[i] = val;
}
int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int gSz = 2*m;
    Edge graph[gSz];
    for(int i=0, _i=(m); i<_i; ++i) {
        scanf("%d %d %lld", &graph[2 * i].a, &graph[2 * i].b, &graph[2 * i].c);
        --graph[2 * i].a;
        --graph[2 * i].b;
        graph[2 * i + 1] = newEdge( graph[2 * i].b, graph[2 * i].a, graph[2 * i].c );
    }
    ll d[2*n]; 
    fill(d, 2*n, INT_MAX);
    d[0] = 0;
    for(int i=0, _i=(2 * n); i<_i; ++i){
        for(int z=0;z<gSz;z++){Edge e = graph[z];
            d[2 * e.b + 1] = min(d[2 * e.b + 1], max(d[2 * e.a    ], e.c +     e.c % 2) + 1);
            d[2 * e.b    ] = min(d[2 * e.b    ], max(d[2 * e.a + 1], e.c + 1 - e.c % 2) + 1);
        }
    }
    ll min_dist = min(d[2 * n - 2], d[2 * n - 1]);
    printf("%lld\n", min_dist == INT_MAX ? -1 : min_dist);
}
