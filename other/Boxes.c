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
int**newmat(int x, int y){
  int**rv = calloc(x, sizeof(int*));
  for(int i=0;i<x;i++)
    rv[i] = calloc(y, sizeof(int));
  return rv;
}

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}

typedef struct vecS {
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;// = malloc(sizeof(vec));
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}


int**memo;
vec*adj;
int*parent;
int*depth;
int*cnt;
int memo0sz;

void dfs(int node){
    for(int z=0;z<adj[node].sz;z++){int x = adj[node].ptr[z];
        depth[x] = depth[node]+1;
        dfs(x);
        cnt[node] += cnt[x];
    }
}
int jump(int node, int amount){
    for(int i = memo0sz-1; i >= 0; --i){
        if(amount&(1<<i))
            node = memo[node][i];
    }
    return node;
}
int main(){
    int n;
    scanf("%d", &n);
    adj   =calloc(n+1,sizeof(vec));
    cnt   =calloc(n+1,sizeof(int)); fill(cnt,n+1,1);
    parent=calloc(n+1,sizeof(int));
    depth =calloc(n+1,sizeof(int));
    int par;
    depth[0] = 0;
    for(int i = 1; i <= n; ++i){
        scanf("%d", &par);
        adj[par].ptr=pushback(adj[par].ptr, &adj[par].sz, i);
        parent[i] = par;
    }
    dfs(0);
    int upper = floor(log2(n))+1;
    memo=newmat(n+1, upper+1);
    memo0sz=upper+1;
    for(int i = 1; i <= n; ++i)
        memo[i][0] = parent[i];
    for(int k = 1; k <= upper; ++k)
        for(int i = 1; i <= n; ++i)
            memo[i][k] = memo[memo[i][k-1]][k-1];
    int q,m;
    scanf("%d", &q);
    while(q--){
        scanf("%d", &m);
        int query[m];
        int valid[m]; fill(valid, m, 1);
        for(int z=0;z<m;z++)
            scanf("%d", &query[z]);
        for(int i = 0; i < m; ++i){
            for(int j = i+1; j < m; ++j){
                if(depth[query[i]] > depth[query[j]]){
                    if(jump(query[i],depth[query[i]]-depth[query[j]]) == query[j])
                        valid[i] = 0;
                } 
                else{
                    if(jump(query[j],depth[query[j]]-depth[query[i]]) == query[i])
                        valid[j] = 0;
                }
            }
        }
        int answer = 0;
        for(int i = 0; i < m; ++i)
            if(valid[i])
                answer += cnt[query[i]];
        printf("%d\n", answer);
    }
    return 0;
}
