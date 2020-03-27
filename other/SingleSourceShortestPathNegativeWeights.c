#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
typedef long long ll;
void fill(ll*arr,ll sz, ll val){
  for(ll i=0;i<sz;i++)
    arr[i]=val;
}
typedef struct{
  ll first, second;
}pair;
pair newpair(ll a, ll b){
  return(pair){a,b};
}
#define pbp(zpv, zvv) zpv.ptr = pushbackP(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
pair*pushbackP(pair*array, ll *size, pair value){
  pair*output = resizeArray(array, pair, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	pair*ptr;
	ll sz;
}vecp;
vecp newVecP(){
	vecp rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
ll INF = 2000000000000ll;
ll n;
ll*dist;
bool*n_cycle;
////////////////////////

void bellmann_ford(vecp*edges, ll source, ll m){
  dist    = calloc(n, sizeof(ll) ); fill(dist, n, INF);
  n_cycle = calloc(n, sizeof(bool));
  dist[source] = 0;
  for(ll iter=0; iter<n-1; ++iter){
    for(ll u=0; u<n; ++u){
      if(dist[u]<INF){
        for(ll z=0;z<edges[u].sz;z++){pair e=edges[u].ptr[z];
          dist[e.first] = fminl(dist[e.first], dist[u] + e.second);
        }
      }
    }
  }
  bool ch=true;
  while(ch){
    ch=false;
    for(ll u=0; u<n; ++u){
      if(dist[u]==INF)
        continue;
      for(ll z=0;z<edges[u].sz;z++){pair e=edges[u].ptr[z];
        if(dist[e.first] > dist[u] + e.second && !n_cycle[e.first]){
          dist[e.first] = -INF;
          ch = true;
          n_cycle[e.first] = true;
        }
      }
    }
  }
}
int main(){
  while(1){
    ll m, q, s;
    scanf("%lld %lld %lld %lld", &n, &m, &q, &s);
    if(n==0&&m==0&&q==0&&s==0)
      break;
    vecp e[n]; clr(e);
    for(ll i=0; i<m; ++i){
      ll u, v, w;
      scanf("%lld %lld %lld", &u, &v, &w);
      pbp(e[u], newpair(v, w));
    }
    bellmann_ford(e, s, m);
    for(ll i=0; i<q; ++i){
      ll x;
      scanf("%lld", &x);
      if(dist[x] == INF)
        puts("Impossible");
      else if(n_cycle[x])
        puts("-Infinity");
      else
        printf("%lld\n", dist[x]);
    }
    puts("");
  }
  return 0;
}
