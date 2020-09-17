#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
inline int max(int a,int b){return a>b?a:b;}
#define swap(a,b) do{ __typeof(a) tp; tp=a; a=b; b=tp; }while(0)
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
//////////////////////////
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int ui;
//typedef pair<int,int> pii;
//typedef vector<vector<int> > graph;
//const double pi = acos(-1.0);
#define oned(a, x1, x2) { cout << #a << ":"; for(int _i = (x1); _i < (x2); _i++){ cout << " " << a[_i]; } cout << endl; }
#define twod(a, x1, x2, y1, y2) { cout << #a << ":" << endl; for(int _i = (x1); _i < (x2); _i++){ for(int _j = (y1); _j < (y2); _j++){ cout << (_j > y1 ? " " : "") << a[_i][_j]; } cout << endl; } }
#define mp make_pair
#define fst first
#define snd second
enum{ MAXN = 200005};
int parent[MAXN<<1];
int Size[MAXN<<1];
int depth = 0;
int par[50][MAXN<<1];
int sz[50][MAXN<<1];
vec mem[50];
int last[MAXN];
int n, m, q, a[MAXN], b[MAXN], l[MAXN], r[MAXN];

void setParent(int v, int p){
    if(par[depth][v]==0) {
        par[depth][v] = parent[v];
        sz[depth][v] = Size[v];
        pb(mem[depth], v);
    }
    parent[v] = p;
}
int getParent(int v){
    while(parent[v] != v) {
        v = parent[v];
    }
    return v;
}
bool mergeSets(int u, int v){
    int pu = getParent(u<<1);
    int pv = getParent(v<<1);
    bool res;
    if((pu>>1) == (pv>>1)) {
        res = pu^pv;
    } 
    else {
        if(Size[pu] > Size[pv]) {
            swap(pu,pv);
        }
        setParent(pu, pv^1);
        Size[pv^1] += Size[pu];
        setParent(pu^1, pv);
        Size[pv] += Size[pu^1];
        res = true;
    }
    return res;
}
void record(){
    depth++;
}
void rollback(){
    for(int i = 0; i < (int)mem[depth].sz; i++){
        int v = mem[depth].ptr[i];
        Size[parent[v]] -= sz[depth][v];
        parent[v] = par[depth][v];
        Size[v] = sz[depth][v];
        par[depth][v] = 0;
    }
    mem[depth].sz=0;
    depth--;
}
void init(){
    for(int i = 2; i <= 2*n+1; i++) {
        parent[i] = i;
        Size[i] = 1;
    }
}
void rec(int L1, int L2, int R1, int R2){
    record();
    int LM = (L1+L2)/2;
    for(int i = L1; i < LM; i++) {
        mergeSets(a[i],b[i]);
    }
    record();
    for(int i = R2; i >= LM; i--) {
        if(!mergeSets(a[i],b[i])) {
            last[LM] = i;
            break;
        }
    }
    rollback();
    if(LM < L2) {
        mergeSets(a[LM],b[LM]);
        rec(LM+1,L2,max(LM+1,last[LM]),R2);
    }
    rollback();
    if(L1 < LM) {
        record();
        for(int i = R2; i > last[LM]; i--) {
            mergeSets(a[i],b[i]);
        }
        rec(L1,LM-1,R1,last[LM]);
        rollback();
    }
}
void solve(){
    init();
    int X = 1;
    while(X <= m) {
        if(!mergeSets(a[X],b[X])) {
            break;
        }
        X++;
    }
    init();
    for(int i = X+1; i <= m; i++) {
        last[i] = m+1;
    }
    if(X <= m) {
        rec(1,X,1,m);
    }
    for(int i = 1; i <= q; i++) {
        printf(last[l[i]] <= r[i] ? "NO\n" : "YES\n");
    }
}
int main(){
    while(scanf("%d %d %d", &n, &m, &q)==3){
        for(int i = 1; i <= m; i++){
            scanf("%d %d", a+i, b+i);
        }
        for(int i = 1; i <= q; i++){
            scanf("%d %d", l+i, r+i);
        }
        solve();
    }
    return 0;
}
