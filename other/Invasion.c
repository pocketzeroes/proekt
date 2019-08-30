#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}

#define pb(zpv, zvv) zpv.ptr = pushbackP(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
typedef struct{
  int first;
  int second;
}pair;
pair newpair(int a, int b){
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

int numSafe;
int*minDist;
vecp*adj;

void dfs(int node, int dist, int*k){
    if(minDist[node] <= dist) 
        return;
    if(minDist[node] == *k)
        numSafe--;
    minDist[node] = dist;
    for(int z=0;z<adj[node].sz;z++){pair to = adj[node].ptr[z];
        dfs(to.first, dist + to.second, k);
    }
}
int main(){
    int n, m, a, k, u, v, w;
    while(scanf("%d%d%d%d", &n, &m, &a, &k)==4){
        if(adj) free(adj);
        adj = calloc(n, sizeof(vecp));
        if(minDist)free(minDist);
        minDist=calloc(n,sizeof(int)); fill(minDist, n, k);
        numSafe = n;
        for(int i=0; i<m; ++i){
            scanf("%d%d%d", &u, &v, &w);
            u--, v--;
            pb(adj[u], newpair(v,w));
            pb(adj[v], newpair(u,w));
        }
        for(int i=0; i<a; ++i){
            scanf("%d", &v);
            if(numSafe > 0)
                dfs(v-1, 0, &k);
            printf("%d\n", numSafe);
        }
        puts("");
    }
    return 0;
}
