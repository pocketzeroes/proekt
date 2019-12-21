#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

#define pb(zpv, zvv) zpv.ptr = pushback(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
typedef struct{
  int first, second;
}pair;
pair newpair(int a, int b){
  return(pair){a,b};
}
#define pbp(zpv, zvv) zpv.ptr = pushbackP(zpv.ptr, &zpv.sz, zvv)
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
/////////////////////////////////////
enum{ MAX_NODES = 50005};


int N, L, S;
bool has  [MAX_NODES];
bool added[MAX_NODES];
vecp neigh[MAX_NODES];
vec  tree [MAX_NODES];
int  memo [MAX_NODES][2];

void dfs(int cur, int from, int sum){
    if(2*sum >= S)
        return;
    for(int i = 0; i < neigh[cur].sz; ++i){
        pair next = neigh[cur].ptr[i];
        if(next.first == from)
            continue;
        pb(tree[cur], next.first);
        dfs(next.first,cur,sum+next.second);
    }
}
int mvc(int cur, int prev){
    int place = 1, 
        dont_place = 0, 
        already_placed = 0;
    if(memo[cur][prev] != -1)
        return memo[cur][prev];
    for(int i = 0; i < tree[cur].sz; ++i){
        int next = tree[cur].ptr[i];
        place += mvc(next,1);
    }
    if(prev){
        for(int i = 0; i < tree[cur].sz; ++i){
            int next = tree[cur].ptr[i];
            dont_place += mvc(next,0);
        }
    }
    if(has[cur]){
        for(int i = 0; i < tree[cur].sz; ++i){
            int next = tree[cur].ptr[i];
            already_placed += mvc(next,1);
        }
    }
    int ret = place;
    if(prev)
        ret = fmin(ret,dont_place);
    if(has[cur])
        ret = fmin(ret,already_placed);
    return memo[cur][prev] = ret;
}
int main(){
    scanf("%d %d", &N, &S);
    for(int i=0; i<N-1; ++i){
        int a, b, d;
        scanf("%d %d %d", &a, &b, &d);
        pbp(neigh[a], newpair(b,d));
        pbp(neigh[b], newpair(a,d));
    }
    scanf("%d", &L);
    for(int i=0; i<L; ++i){
        int cur;
        scanf("%d", &cur);
        has[cur] = true;
    }
    memset(memo, -1, sizeof(memo));
    added[1] = true;
    dfs(1, -1, 0);
    printf("%d\n", (int)fmin(mvc(1,1),mvc(1,0)));
    return 0;
}
