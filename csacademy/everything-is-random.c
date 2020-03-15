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
////////////////////////

typedef long long ll;

enum{ N  = (int)(1e5) + 10};
enum{ H  = (int)(3e3) + 10};
enum{ MOD= (int)(1e9) + 7};

int dp[N];
int inv[N];
int fact[N];
int ifact[N];

int nCk(int n, int k) {
    return fact[n] * 1LL * ifact[k] % MOD * ifact[n - k] % MOD;
}
int n;
int a[N];
vec adj[N];
int ans;
vec branch;

void dfs(int at, int from){
    pb(branch, a[at]);
    for(int len=1; len <= branch.sz; len++){
        int _a = branch.ptr[branch.sz-len];
        ans += _a * 1LL * dp[len] % MOD * nCk(n, len) % MOD * fact[n - len] % MOD;
        ans %= MOD;
    }
    for(int z=0;z<adj[at].sz;z++){int to = adj[at].ptr[z];
        if(to != from)
            dfs(to, at);
    }
    branch.sz--;
}
int main(){
    inv[1] = fact[0] = ifact[0] = 1;
    for(int i = 2; i < N; i++) inv[i] = inv[MOD % i] * 1LL * (MOD - MOD / i) % MOD;
    for(int i = 1; i < N; i++) fact[i] = fact[i - 1] * 1LL * i % MOD;
    for(int i = 1; i < N; i++) ifact[i] = ifact[i - 1] * 1LL * inv[i] % MOD;
    for(int h = 1; h < H; h++){
        for(int len = 1; len <= h; len++){
            dp[h] += nCk(h - 1, len - 1) * 1LL * nCk(h, len) % MOD * fact[h - len] % MOD;
            dp[h] %= MOD;
        }
    }
    scanf("%d", &n);
    for(int i=1; i<=n-1; i++){
        int u, v;
        scanf("%d %d", &u, &v);
        pb(adj[u], v);
        pb(adj[v], u);
    }
    for(int i=1; i<=n; i++)
        scanf("%d", &a[i]);
    dfs(1, 0);
    for(int i=1; i<=n; i++){
        ans += a[i] * 1LL * fact[n] % MOD;
        ans %= MOD;
    }
    printf("%d\n", ans);
    return 0;
}
