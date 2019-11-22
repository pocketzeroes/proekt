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

enum{ MAXN = 100000};
int n;
int c[MAXN], k[MAXN];
double a[MAXN];
vec tree[MAXN];

double dfs(int u, int p){
    double s = a[u];
    for(int z=0;z<tree[u].sz;z++){int v = tree[u].ptr[z];
        if(v == p)
            continue;
        s += fmax(0.0, dfs(v, u));
    }
    return s;
}
bool works(double m){
    for(int i=0; i<n; ++i)
        a[i] = c[i] - m * k[i];
    return dfs(0, -1) > 0.0;
}
int main(){
    scanf("%d", &n);
    for(int i=0; i<n; ++i)
        scanf("%d", &c[i]);
    for(int i=0; i<n; ++i)
        scanf("%d", &k[i]);
    for(int i = 1; i < n; ++i){
        int u, v;
        scanf("%d %d", &u, &v);
        --u, --v;
        pb(tree[u], v);
        pb(tree[v], u);
    }
    double lo = 0.0;
    double hi = 1e6 + 7;
    for(int iter = 0; iter < 100; ++iter){
        double mid = (lo + hi) / 2;
        if(works(mid))
            lo = mid;
        else
            hi = mid;
    }
    printf("%.12lf\n", hi);
    return 0;
}
