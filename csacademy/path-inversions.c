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
typedef struct vecS {
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
////////////
typedef long long ll;

enum{ N = 100000 };
enum{ MOD = (int)(1e9) + 7};
int n, k;
vec g    [N];
int gsz  [N];
bool used[N];
int cnt  [N];
ll ans;
int delta;

void calcSizes(int v, int p){
    gsz[v] = 1;
    for(int z=0;z<g[v].sz;z++){int to = g[v].ptr[z];
        if (used[to] && to != p){
            calcSizes(to, v);
            gsz[v] += gsz[to];
        }
    }
}
void dfs(int v, int par, int dist){
    cnt[dist] += delta;
    for(int z=0;z<g[v].sz;z++){int to = g[v].ptr[z];
        if (used[to] && to != par) {
            dfs(to, v, dist + 1);
        }
    }
}
void dfs2(int v, int par, int dist){
    if (dist <= k){
        ans += cnt[k - dist];
    }
    for(int z=0;z<g[v].sz;z++){int to = g[v].ptr[z];
        if (used[to] && to != par) {
            dfs2(to, v, dist + 1);
        }
    }
}
void solvei(int v){
    cnt[0] = 2;
    delta = 1;
    for(int z=0;z<g[v].sz;z++){int to = g[v].ptr[z];
        if (used[to]) {
            dfs(to, v, 1);
        }
    }
    for(int z=0;z<g[v].sz;z++){int to = g[v].ptr[z];
        if (used[to]) {
            delta = -1;
            dfs(to, v, 1);
            dfs2(to, v, 1);
            delta = 1;
            dfs(to, v, 1);
        }
    }
    delta = -1;
    for(int z=0;z<g[v].sz;z++){int to = g[v].ptr[z];
        if (used[to]) {
            dfs(to, v, 1);
        }
    }
}
void cd(int v, int p){
    calcSizes(v, -1);
    int tot = gsz[v];
    bool ok = false;
    int pp  = -1;
    while (!ok){
        ok = true;
        for(int z=0;z<g[v].sz;z++){int to = g[v].ptr[z];
            if (used[to] && to != pp && gsz[to] * 2 > tot){
                pp = v;
                v  = to;
                ok = false;
                break;
            }
        }
    }
    solvei(v);
    used[v] = false;
    for(int z=0;z<g[v].sz;z++){int to = g[v].ptr[z];
        if (used[to])
            cd(to, v);
    }
}
int solve(){
    ans = 0;
    for (int i = 0; i < (int)(n); ++i) 
        used[i] = true;
    cd(0, -1);
    assert(ans % 2 == 0);
    ans /= 2;
    return (ll)k * (k + 1) / 2 % MOD * (ans % MOD) % MOD;
}
void readTest(){
    scanf("%d %d", &n, &k);
    for (int i = 0; i < (int)(n); ++i) 
        g[i].sz=0;
    for (int i = 0; i < (int)(n - 1); ++i){
        int from, to;
        scanf("%d %d", &from, &to), --from, --to;
        g[from].ptr = pushback(g[from].ptr, &g[from].sz, to  );
        g[to  ].ptr = pushback(g[to  ].ptr, &g[to  ].sz, from);
    }
}
int main(){
    readTest();
    printf("%d\n", solve());
    return 0;
}
