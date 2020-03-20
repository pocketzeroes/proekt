#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
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
//////////////////////////////////////
enum{ MAXN = 200005};

int n, q;
vec gph[MAXN];
int par[19][MAXN],
    dep[MAXN];

int lca(int x, int y){
    if(dep[x] < dep[y])
        swap(x, y);
    int ret = dep[x] - dep[y];
    for(int i=0; i<19; i++){
        if(ret & (1<<i))
            x = par[i][x];
    }
    for(int i=18; i>=0; i--){
        if(par[i][x] != par[i][y]){
            x = par[i][x];
            y = par[i][y];
        }
    }
    if(x != y)
        return par[0][x];
    return x;
}
int dis(int x, int y){
    return dep[x] + dep[y] - 2 * dep[lca(x, y)];
}
void dfs(int x, int p){
    for(int z=0;z<gph[x].sz;z++){int i=gph[x].ptr[z];
        if(i!=p){
            dep[i] = dep[x] + 1;
            par[0][i] = x;
            dfs(i, x);
        }
    }
}
int main(){
    scanf("%d %d", &n, &q);
    for(int i=1; i<n; i++){
        int s, e;
        scanf("%d %d", &s, &e);
        pb(gph[s], e);
        pb(gph[e], s);
    }
    dfs(1, 0);
    for(int i=1; i<19; i++)
        for(int j=1; j<=n; j++)
            par[i][j]  = par[i-1][par[i-1][j]];
    while(q--){
        int x, y;
        scanf("%d %d",&x,&y);
        int d = dis(x, y);
        printf("%lld\n", n + 1ll * d * (d + 1) / 2);
    }
    return 0;
}
