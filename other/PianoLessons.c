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
vec newVec(){
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

vec*G;
int*L;   int Lsz;
int*R;
int*Viz; int VizSz;

void BipartiteMatcher(int n, int m){
    G   = calloc(n, sizeof(vec));
    L   = calloc(n, sizeof(int)); fill(L, n, -1); Lsz=n;
    R   = calloc(m, sizeof(int)); fill(R, m, -1);
    Viz = calloc(n, sizeof(int));
    VizSz=n;
}
void AddEdge(int a, int b){
    G[a].ptr = pushback(G[a].ptr, &G[a].sz, b);
}
bool Match(int node){
    if(Viz[node])
        return false;
    Viz[node] = true;
    for(int i=0;i<G[node].sz;i++){int mvc = G[node].ptr[i];
        if(R[mvc] == -1 || Match(R[mvc])){
            L[node] = mvc;
            R[mvc] = node;
            return true;
        }
    }
    return false;
}
int Solve(){
    bool ok = true;
    while(ok){
        ok = false;
        fill(Viz, VizSz, 0);
        for(int i = 0; i < Lsz; ++i)
            if(L[i] == -1)
               ok |= Match(i);
    }
    int ret = 0;
    for(int i = 0; i < Lsz; ++i)
        ret += (L[i] != -1);
    return ret;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    BipartiteMatcher(n, m);
    for(int i=0; i<n; ++i){
        int size;
        scanf("%d", &size);
        for(int j=0; j<size; ++j){
            int slot;
            scanf("%d", &slot);
            AddEdge(i, slot-1);
        }
    }
    printf("%d\n", Solve());
    return 0;
}
