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

typedef long long ll;
vec*edges;
enum{ MOD = 1000000009};
int cache[1000][1000];

int color(int e, int k, int r){
    if(cache[e][r] == -1){
        if(e > k - r)
            cache[e][r] = 0;
        else{
            ll ans = 1;
            for(int i = 0; i < e; i++)
                ans = (ans * (k - r - i)) % MOD;
            cache[e][r] = ans;
        }
    }
    return cache[e][r];
}
ll recurse(int x, int p, int k){
    int r = p == -1 ? 0 : edges[p].sz;
    ll ans = color(edges[x].sz - (p == -1 ? 0 : 1), k, r);
    for(size_t i = 0; i < edges[x].sz; i++)
        if(edges[x].ptr[i] != p)
            ans = (ans * recurse(edges[x].ptr[i], x, k)) % MOD;
    return ans;
}
int main(){
    int cases;
    scanf("%d", &cases);
    for(int cas = 0; cas < cases; cas++){
        printf("Case #%d: ", cas + 1);
        int n, k;
        scanf("%d %d", &n, &k);
        memset(cache, -1, sizeof(cache));
        if(edges)free(edges);
        edges=calloc(n, sizeof(vec));
        for (int i = 1; i < n; i++){
            int a, b;
            scanf("%d %d", &a, &b);
            a--, b--;
            pb(edges[a], b);
            pb(edges[b], a);
        }
        printf("%d\n", (int)recurse(0, -1, k));
    }
    return 0;
}
