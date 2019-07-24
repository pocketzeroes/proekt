#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
typedef struct{
    int f, s, t;
}edge;
edge newEdge(int a, int b, int c){
    edge rez;
    rez.f = a;
    rez.s = b;
    rez.t = c;
    return rez;
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
edge*pushbackE(edge*array, int *size, edge value){
  edge*output = resizeArray(array, edge, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	edge*ptr;
	int sz;
}vece;
vece newVecE(){
	vece rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
int cmpE(const void*pa, const void*pb){
    edge*a = (edge*)pa;
    edge*b = (edge*)pb;
    if(a->f != b->f) return a->f - b->f;
    if(a->s != b->s) return a->s - b->s;
    if(a->t != b->t) return a->t - b->t;
    return 0;
}
///////////////////////

enum{ MAXN = 1003};
int n, m, p;
bool is_insec[MAXN];

int uf[MAXN];

void init(){
    for (int i = 1; i <= n; ++i)
        uf[i] = i;
}
int find(int x){
    return uf[x] = uf[x] == x ? x : find(uf[x]);
}
int merge(int x, int y){
    int xr = find(x);
    int yr = find(y);
    if (xr == yr)
        return false;
    uf[xr] = yr;
    return true;
}
int main(){
    scanf("%d %d %d", &n, &m, &p);
    int u, v, w;
    for (int i = 0; i < p; ++i){
        scanf(" %d", &u);
        is_insec[u] = true;
    }
    vece insecs = newVecE();
    vece safe   = newVecE();
    for (int i = 0; i < m; ++i){
        scanf("%d %d %d", &u, &v, &w);
        if (is_insec[u] ^ is_insec[v])
            insecs.ptr = pushbackE(insecs.ptr, &insecs.sz, newEdge(w, u, v));
        else if((!is_insec[u] && !is_insec[v]) || (p == n))
            safe.ptr = pushbackE(safe.ptr, &safe.sz, newEdge(w, u, v));
    }
    qsort(insecs.ptr, insecs.sz, sizeof(edge), cmpE);
    qsort(safe  .ptr, safe  .sz, sizeof(edge), cmpE);
    init();
    ll cost = 0;
    for(int z=0;z<safe.sz;z++){edge e = safe.ptr[z];
        int w = e.f;
        int u = e.s;
        int v = e.t;
        if(merge(u, v))
            cost += w;
    }
    int safe_one = -1;
    for (int i = 1; i <= n; ++i){
        if (!is_insec[i])
            safe_one = i;
    }
    if(safe_one != -1){
        for (int i = 1; i <= n; ++i) {
            if (!is_insec[i] && find(safe_one) != find(i)){
                printf("impossible\n");
                return 0;
            }
        }
    }
    for(int z=0; z<insecs.sz; z++){edge e = insecs.ptr[z];
        int w = e.f;
        int u = e.s;
        int v = e.t;
        if(merge(u, v))
            cost += w;
    }
    for(int i = 1; i <= n; ++i){
        if (find(1) != find(i)){
            printf("impossible\n");
            return 0;
        }
    }
    printf("%lld\n", cost);
    return 0;
}
