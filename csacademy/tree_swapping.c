#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdint.h>
#include<assert.h>
#include<stdbool.h>

int64_t min(int64_t a,int64_t b){return a<b?a:b;}
int64_t max(int64_t a,int64_t b){return a>b?a:b;}

typedef struct pair{
    int first;
    int second;
}pair;
pair newPair(int a, int b){
    pair rez;
    rez.first =a;
    rez.second=b;
    return rez;
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}

enum{ N = 100000};
const int inf = (int)1e8 + 1;
const long long big = (long long)1e18 + 1;
const int P = 31;
const int MOD = (int)1e9 + 7;
const int MOD1 = (int)1e9 + 9;


#define MAX_STR_SZ 100000
char type[MAX_STR_SZ];
int*g      [N];
int sizes  [N];
int height [N];
int sz     [N];
int cnt    [N];
int cnt_red[N];

void dfs(int u, int p, int t, int h)
{
    height[u] = h;
    sz[u] = 1;
    if (t == 1)
        cnt[u] = 1;
    if (type[u] == 'R')
        cnt_red[u] = 1;
    for(int i=0;i<sizes[u];i++){
        int v = g[u][i];
        if (v != p)
        {
            dfs(v, u, 1 - t, h + 1);
            sz     [u] += sz     [v];
            cnt    [u] += cnt    [v];
            cnt_red[u] += cnt_red[v];
        }
    }
}
int main()
{
    int n;
    scanf("%d %s", &n, &type);
    pair edge[n - 1];
    memset(edge, 0, sizeof(edge));
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        scanf("%d %d",  &u,  &v);
        u--; v--;
        g[u]=pushback(g[u], sizes+u, v);
        g[v]=pushback(g[v], sizes+v, u);
        edge[i] = newPair(u, v);
    }
    dfs(0, -1, 1, 0);
    long long ans_r = 0, ans_b = 0;
    for(int z=0; z<n-1; z++){
        pair i = edge[z];
        int u = i.first, v = i.second;
        if (height[u] > height[v]){
            int t;
            t=u; u=v; v=t;
        }
        ans_r += abs(cnt[v] - cnt_red[v]);
        ans_b += abs((sz[v] - cnt[v]) - cnt_red[v]);
    }
    long long ans = big;
    if (cnt[0] == cnt_red[0])
        ans = min(ans, ans_r);
    if (cnt[0] == n - cnt_red[0])
        ans = min(ans, ans_b);
    if (ans == big)
        puts("-1");
    else
        printf("%lld\n", ans);
    return 0;
}




























































