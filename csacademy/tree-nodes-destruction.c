#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<stdint.h>
#include<limits.h>

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}


enum{ N =(int) 1e5 + 10};
enum{ K =(int) 30      };
int n, m;
int*adj  [N];
int sizes[N];
int dp[K][N];
int prof[N];
int st[N], ed[N], t;
typedef struct pathS
{
    int x, y, join, dis;
}path;
path*pushbackP(path *array, int*size, path value){
    path *output = resizeArray(array, path, *size + 1);
    output[(*size)++] = value;
    return output;
}
path newPath(int x, int y, int join, int dis){
    path rez;
    rez.x    = x;
    rez.y    = y;
    rez.join = join;
    rez.dis  = dis;
    return rez;
}
path*P=NULL;int PSz=0;

int cmpP(const void*pa, const void*pb)
{
    path*A=(path*)pa;
    path*B=(path*)pb;
    return (A->dis > B->dis)?-1:1;
}
typedef struct BITs
{
    int bit[N];
}bit;

bit*gBit;

void update(bit*b, int idx, int val)
{
    while (idx < N)
    {
        b->bit[idx] += val;
        idx += (idx & -idx);
    }
}
int query (bit*b, int idx)
{
    int ans = 0;
    while (idx > 0)
    {
        ans += b->bit[idx];
        idx -= (idx & -idx);
    }
    return ans;
}
int range(bit*b, int L, int R)
{
    update(b, L, +1);
    update(b, R + 1, -1);
}
void dfs (int v)
{
    st[v] = ++t;
    for(int i=0;i<sizes[v];i++){
        int u=adj[v][i];
        if (u != dp[0][v])
        {
            dp[0][u] = v;
            prof[u] = prof[v] + 1;
            dfs (u);
        }
    }
    ed[v] = t;
}
int lca (int x, int y)
{
    int t;
    if (prof[y] < prof[x]){
        t=x; x=y; y=t;
    }
    int d = prof[y] - prof[x];
    for (int k = K - 1; k >= 0; k--)
        if ((1 << k) & d)
            y = dp[k][y];
    if (x == y)
        return x;
    for (int k = K - 1; k >= 0; k--)
        if (dp[k][x] != dp[k][y])
        {
            x = dp[k][x];
            y = dp[k][y];
        }
    return dp[0][x];
}
int solve ()
{
    int ans = 0;
    qsort(P, PSz, sizeof(path), cmpP);
    for(int z=0;z<PSz;z++){
        path i=P[z];
        int u = i.x;
        int v = i.y;
        int LCA = i.join;
        if (!query(gBit, st[u]) && !query(gBit, st[v]))
        {
            ans++;
            range(gBit, st[LCA], ed[LCA]);
        }
    }
    return ans;
}
int main ()
{
    gBit=malloc(sizeof(bit));
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n - 1; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u]=pushback(adj[u], sizes+u, v);
        adj[v]=pushback(adj[v], sizes+v, u);
    }
    dp[0][1] = 1;
    dfs (1);
    for (int k = 1; k < K; k++)
        for (int i = 1; i <= n; i++)
            dp[k][i] = dp[k - 1][dp[k - 1][i]];
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        int LCA = lca (u, v);
        P=pushbackP(P, &PSz, newPath(u, v, LCA, prof[LCA]));
    }
    printf("%d\n", solve());
    return 0;
}




























































