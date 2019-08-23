#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

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
  int first;
  int second;
}pair;
pair newPair(int a, int b){
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
int cmpP(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}


int*pset;
void DSU(int n){
    pset=calloc(n, sizeof(int));
    for(int i=0; i<=n-1; ++i)
        pset[i] = i;
}
int findSet(int i){
    if(pset[i] == i)
        return i;
    else{
        pset[i] = findSet(pset[i]);
        return pset[i];
    }
}
bool unionSet(int u, int v){
    int p = findSet(u), 
        q = findSet(v);
    if(p == q)
        return false;
    pset[p] = q;
    return true;
}

vec g[1000005];
int n, m, dp[1000005];

int toInd(int r, int c){
    return r*m+c;
}
int Solve(int u) {
    if (dp[u] != -1)
        return dp[u];
    int res = 1;
    for(int z=0;z<g[u].sz;z++){int it = g[u].ptr[z];
        int v = it;
        res = fmax(res, Solve(v)+1);
    }
    return dp[u] = res;
}
int main(){
    scanf("%d%d", &n, &m);
    int a[n][m]; memset(a, 0, sizeof(a));
    for(int i = 0; i <= n-1; ++i) 
        for(int j = 0; j <= m-1; ++j) 
            scanf("%d", &a[i][j]);
    DSU(n*m);
    for(int i = 0; i <= n-1; ++i) {
        vecp p=newVecP();
        for(int j = 0; j <= m-1; ++j)
            p.ptr = pushbackP(p.ptr, &p.sz, newPair(a[i][j], j));
        qsort(p.ptr, p.sz, sizeof(pair), cmpP);
        for(int j = 1; j <= m-1; ++j){
            if(p.ptr[j].first == p.ptr[j-1].first)
                unionSet(toInd(i, p.ptr[j].second), toInd(i, p.ptr[j-1].second));
        }
    }
    for(int j = 0; j <= m-1; ++j) {
        vecp p = newVecP();
        for(int i = 0; i <= n-1; ++i)
            p.ptr = pushbackP(p.ptr, &p.sz, newPair(a[i][j], i));
        qsort(p.ptr, p.sz, sizeof(pair), cmpP);
        for(int i = 1; i <= n-1; ++i) {
            if (p.ptr[i].first == p.ptr[i-1].first) unionSet(toInd(p.ptr[i].second, j), toInd(p.ptr[i-1].second, j));
        }
    }
    for(int i = 0; i <= n-1; ++i){
        vecp p=newVecP();
        for(int j = 0; j <= m-1; ++j)
            p.ptr = pushbackP(p.ptr, &p.sz, newPair(a[i][j], j));
        qsort(p.ptr, p.sz, sizeof(pair), cmpP);
        for(int j = 1; j <= m-1; ++j){
            if (p.ptr[j].first != p.ptr[j-1].first){
                int idx=findSet(toInd(i, p.ptr[j-1].second));
                g[idx].ptr = pushback(g[idx].ptr, &g[idx].sz, findSet(toInd(i, p.ptr[j].second)));
            }
        }
    }
    for(int j = 0; j <= m-1; ++j) {
        vecp p=newVecP();
        for(int i = 0; i <= n-1; ++i)
            p.ptr = pushbackP(p.ptr, &p.sz, newPair(a[i][j], i));
        qsort(p.ptr, p.sz, sizeof(pair), cmpP);
        for(int i = 1; i <= n-1; ++i) {
            if (p.ptr[i].first != p.ptr[i-1].first){
                int idx=findSet(toInd(p.ptr[i-1].second, j));
                g[idx].ptr = pushback(g[idx].ptr, &g[idx].sz,findSet(toInd(p.ptr[i].second, j)));
            }
        }
    }
    for(int i = 0; i <= n*m-1; ++i)
        dp[i] = -1;
    int ans = 0;
    for(int i = 0; i <= n*m-1; ++i)
        ans = fmax(ans, Solve(i));
    printf("%d", ans);
    return 0;
}
