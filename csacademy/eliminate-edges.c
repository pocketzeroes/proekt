#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

#define swap(a,b) do\
    {\
      a ^= b;\
      b ^= a;\
      a ^= b;\
    } while (0)

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

/////////////////
typedef long long ll;
enum{ N = 10000};
int dp[15][N];
int n;
int m;
int p[N];
vec*g;
pair e  [25000];
int  d  [N];
vec  rep[N];
bool vis[25000];
int  res;


int find(int u){
    if (p[u] == u)
        return u;
    return p[u] = find(p[u]);
}
void DFS(int u, int p){
    dp[0][u] = p;
    for (int i = 0; i<g[u].sz; ++i)
        if(g[u].ptr[i] != p) {
            d[g[u].ptr[i]] = d[u] + 1;
            DFS(g[u].ptr[i], u);
        }
}
int LCA(int a, int b){
    if (d[a] < d[b])
        swap(a, b);
    int l = 0;
    while ((1 << l) <= d[a])
        ++l;
    --l;
    for (int i = l; i >= 0; --i)
        if (d[a] - (1 << i) >= d[b])
            a = dp[i][a];
    if (a == b)
        return a;
    for (int i = l; i >= 0; --i)
        if (dp[i][a] != dp[i][b]) {
            a = dp[i][a];
            b = dp[i][b];
        }
    return dp[0][a];
}
void add(int u, int p, int e){
    int *parent = dp[0];
    while (u != p){
        rep[u].ptr = pushback(rep[u].ptr, &rep[u].sz, e);
        u = parent[u];
    }
}
bool rem(int u, int p){
    int *parent = dp[0];
    while(u != p){
        while(rep[u].sz>0){
#define rep_u_back rep[u].ptr[rep[u].sz-1]
            if (vis[rep_u_back])
                rep[u].sz--;
            else{
                res = rep_u_back;
                rep[u].sz--;
                vis[res] = true;
                return true;
            }
        }
        u = parent[u];
    }
    return false;
}
int main(){
    scanf("%d", &n);
    g = calloc(n, sizeof(vec));
    scanf("%d", &m);
    int q;
    scanf("%d", &q);
    vec o = newVec();
    for (int i = 0; i < n; ++i)
        p[i] = i;
    for (int i = 0, a, b; i < m; ++i){
        scanf("%d %d", &a, &b);
        --a; --b;
        e[i].first  = a;
        e[i].second = b;
        if(find(a) != find(b)){
            p[find(a)] = find(b);
            g[a].ptr = pushback(g[a].ptr, &g[a].sz, b);
            g[b].ptr = pushback(g[b].ptr, &g[b].sz, a);
        }
        else
            o.ptr = pushback(o.ptr, &o.sz, i);
    }
    memset(dp, -1, sizeof(dp));
    DFS(0, -1);
    for(int k = 1; (1 << k) < n; ++k)
        for(int i = 0; i < n; ++i)
            if(dp[k - 1][i] != -1)
                dp[k][i] = dp[k - 1][dp[k - 1][i]];
    for(int i = 0; i < o.sz; ++i){
        pair ee = e[o.ptr[i]];
        int u = ee.first;
        int v = ee.second;
        int c = LCA(u, v);
        add(u, c, o.ptr[i]);
        add(v, c, o.ptr[i]);
    }
    int u, v;
    while (q--){
        scanf("%d %d", &u, &v);
        --u; --v;
        int c = LCA(u, v);
        if(rem(u, c) || rem(v, c))
            printf("0 %d %d\n", e[res].first + 1, e[res].second + 1);
        else
            printf("1\n");
        fflush(stdout);
    }
    return 0;
}
