#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int cmp(const void * a, const void * b){ return ( *(int*)a - *(int*)b );}

enum{ N = 1001};

typedef struct Node{
    int a, b, id, val;
}Node;
Node s[N];

typedef struct data{
    int id, v, nxt;
}data;
data e[N<<1];

typedef struct edge{
    int u, pre, id;
}edge;
edge Que[N];

int fa[N], ans[N], head[N];
int n, m, tot, cnt, l, r;
bool vis[N], yi[N];


int cmpN(const void*pa, const void*pb){
    Node*a=(Node*)pa;
    Node*b=(Node*)pb;
    return(a->val > b->val)?-1:1;
}
int Find(int x){
    if (fa[x] != x)
        fa[x] = Find(fa[x]);
    return fa[x];
}
bool Check(int x, int y){
    int fx = Find(x);
    int fy = Find(y);
    return fx == fy;
}
void Kruskal(int n, int m){
    int fx, fy;
    qsort(s, m, sizeof(Node), cmpN);
    for (int i = 0; i < m; ++i) {
        fx = Find(s[i].a);
        fy = Find(s[i].b);
        if (fx != fy) {
            ans[tot++] = i;
            fa[fx] = fy;
        }
        if (Check(0, n - 1))
            break;
    }
}
int main(){
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++i) {
        scanf("%d%d%d", &s[i].a, &s[i].b, &s[i].val);
        s[i].id = i;
    }
    for (int i = 0; i < n; ++i)
        fa[i] = i;
    Kruskal(n, m);
    cnt = 1;
    for (int i = 0; i < tot; ++i) {
        e[cnt] = (data) {
                ans[i], s[ans[i]].b, head[s[ans[i]].a]
        };
        head[s[ans[i]].a] = cnt++;
        e[cnt] = (data) {
                ans[i], s[ans[i]].a, head[s[ans[i]].b]
        };
        head[s[ans[i]].b] = cnt++;
    }
    l = -1;
    Que[0].u = 0;
    vis[0] = true;
    edge now, nxx;
    while (l < r) {
        now = Que[++l];
        for (int i = head[now.u]; i; i = e[i].nxt) {
            nxx.u = e[i].v;
            if (!vis[nxx.u]) {
                nxx.pre = l;
                nxx.id = e[i].id;
                vis[nxx.u] = true;
                Que[++r] = nxx;
            }
        }
    }
    int i;
    for (i = r; i >= 0; --i)
        if (Que[i].u == n - 1) break;
    memset(vis,0,sizeof(vis));
    vis[0] = true;
    while (i) {
        vis[s[Que[i].id].b] = vis[s[Que[i].id].a] = yi[Que[i].id] = true;
        i = Que[i].pre;
    }
    tot = 0;
    for (i = 0; i < m; ++i) {
        if ((vis[s[i].a] || vis[s[i].b]) && !yi[i]) ans[tot++] = s[i].id;
    }
    if (tot == 0)
        printf("none\n");
    else {
        qsort(ans, tot, sizeof(int), cmp);
        for (i = 0; i < tot - 1; ++i)
            printf("%d ", ans[i]);
        printf("%d\n", ans[tot - 1]);
    }
    return 0;
}
