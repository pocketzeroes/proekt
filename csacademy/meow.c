#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>



#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}


typedef long long ll;
enum{ N   =(int) 3e5 + 7};
enum{ MOD =(int) 1e9 + 7};

int val[N], 
    prv[N];
int p  [N];
int*adj[N];
int  sz[N];
int dp [N];
int tmp[N];
int up [N];
int ans[N];
int s  [N];
int cnt[N];
int n, l, q;

int cmp(const void*pa,const void*pb)
{
    int*ptra=(int*)pa;
    int*ptrb=(int*)pb;
    int a = *ptra;
    int b = *ptrb;
    return (cnt[a] < cnt[b])?-1:1;
}
int add(int*a, int b)
{
    (*a) += b;
    if (*a >= MOD)
        (*a) -= MOD;
    if (*a < 0)
        (*a) += MOD;
    return *a;
}
void DFS(int v, int k)
{
    add(&dp[prv[v]], (k * tmp[v] + MOD) % MOD);
    for(int i=0;i<sz[v];i++){int u = adj[v][i];
        DFS(u, k);
    }
}
int best(int x)
{
    int UP = 0, DOWN = 0;
    if (x == 0)
        UP = 1;
    else
        UP = up[x - 1];
    if (x == l-1)
        DOWN = 1;
    else
        DOWN = dp[x + 1];
    return 1LL * DOWN * UP % MOD;
}
void dfs(int v, bool save)
{
    if (val[v] == 0)
        add(&up[0], 1);
    else 
        add(&up[val[v]], up[val[v]-1]);
    for(int i=0;i<sz[v];i++){int u = adj[v][i];
        if (u != adj[v][sz[v]-1])
            dfs(u, 0);
        else
            dfs(u, 1);
    }
    if (val[v] == 0)
        add(&up[0], -1);
    else
        add(&up[val[v]], -up[val[v]-1]);
    for(int i=0;i<sz[v];i++){int u = adj[v][i];
        if (u != adj[v][sz[v]-1])
            DFS(u, 1);
    }
    tmp[v] = 0;
    if (prv[v] == l-1)
        add(&tmp[v], 1);
    else
        add(&tmp[v], dp[prv[v]+1]);
    ans[v] = 0;
    add(&ans[v],  best(val[v]));
    add(&ans[v], -best(prv[v]));
    if (save)
        add(&dp[prv[v]], tmp[v]);
    else
        for(int i=0;i<sz[v];i++){int u = adj[v][i];
            DFS(u, -1);
        }
}
int main()
{
    scanf("%d %d %d",&n,&l,&q);
    p[0] = -1;
    for (int i=1; i<n; i++)
    {
        scanf("%d", &p[i]);
        int idx=p[i];
        adj[idx]=pushback(adj[idx], sz+idx, i);
    }
    for (int i=n-1; i>0; i--)
    {
        cnt[i]++;
        cnt[p[i]] += cnt[i];
        qsort(adj[i], sz[i], sizeof(int), cmp);
    }
    for (int i=0; i<n; i++)
    {
        scanf("%d", &s[i]);
        s[i]--;
    }
    for (int i=0; i<q; i++)
    {
        scanf("%d", &s[i+n]);
        s[i+n]--;
    }
    q += n;
    int Ans = 0;
    if (l == 1)
        Ans = n;
    int res = 0;
    for (int x=0; x<q; x+=n)
    {
        for (int i=0; i<n; i++)
            prv[i] = val[i];
        for (int i=0; i<n; i++)
            if (x + i < q)
                val[i] = s[x + i];
        dfs(0, 0);
        for (int i=0; i<n; i++)
        {
            add(&Ans, ans[i]);
            if (x+i>=n && x+i<q)
                res = add(&res, 1LL * (x+i-n+1) * Ans % MOD);
        }
    }
    printf("%d\n", res);
    return 0;
}



























































