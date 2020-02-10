#pragma GCC optimize "-O3"
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
#define swap(a,b) do{ __typeof(a) tp; tp = a; a = b; b = tp; }while(0)
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
enum{ MAXN = 10005};

int N, M, UF[MAXN], SZ[MAXN], DEP[MAXN], PAR[MAXN];
vec adj[MAXN];
vecp spare;

int find(int v){
    if(UF[v] < 0)
        return v;
    else
        UF[v] = find(UF[v]);
    return UF[v];
}
bool join(int v, int w){
    v = find(v), 
    w = find(w);
    if (v == w) 
        return false;
    if (UF[v] > UF[w]) 
        swap(v, w);
    UF[v] += UF[w];
    UF[w] = v;
    return true;
}
void dfs(int v, int prev, int dep){
    DEP[v] = dep;
    PAR[v] = prev;
    for(int z=0;z<adj[v].sz;z++){int w = adj[v].ptr[z];
        if(w != prev)
            dfs(w, v, dep + 1);
    }
}
int main(){
    scanf("%d %d", &N, &M);
    fill(UF, N, -1);
    for(int i = 0, a, b; i < M; i++){
        scanf("%d %d", &a, &b);
        if(join(a, b)){
           pb(adj[a], b);
           pb(adj[b], a);
        }
        else
            pbp(spare, newpair(a, b));
    }
    fill(UF, N, -1);
    fill(SZ, N, 1);
    dfs(0, -1, 0);
    for(int z=0;z<spare.sz;z++){pair e = spare.ptr[z];
        int a = e.first, 
            b = e.second;
        while((a = find(a)) != (b = find(b))){
            if(DEP[a] < DEP[b])
                swap(a, b);
            int fpa = find(PAR[a]);
            UF[a] = fpa;
            SZ[fpa] += SZ[a];
            a = PAR[a];
        }
    }
    printf("%d\n", SZ[0]);
    return 0;
}
