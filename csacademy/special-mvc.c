#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}


enum{ N =(int) 2e5 + 10};

typedef struct edgeS{ int to, pre; }edge;
edge e[N << 1];
int u[N], l = 0;
void ins(int a, int b) { e[++l] = (edge){b, u[a]}, u[a] = l; }

int n, m;
int pre[N], low[N], dfn = 0, st[N], top = 0, f[N], g[N];

void dfs(int x, int fa) {
    pre[x] = low[x] = ++dfn, st[++top] = x;
    int fx = 1, gx = 0;
    for(int i = u[x]; i; i = e[i].pre) if (e[i].to != fa) {
        if (!pre[e[i].to]) {
            dfs(e[i].to, x), low[x] = min(low[x], low[e[i].to]);
            if (pre[x] <= low[e[i].to]) {
                static int F[2][2][2];
                F[0][0][0] = F[0][1][1] = 0;
                F[0][0][1] = F[0][1][0] = n + 1;
                int t = 0;
                while (st[top + 1] != e[i].to) {
                    int cur = st[top--];
                    for(int d0 = 0; d0 < 2; d0++) for(int d = 0; d < 2; d++) F[t^1][d0][d] = n + 1;
                    for(int d0 = 0; d0 < 2; d0++) for(int d = 0; d < 2; d++) for(int d1 = 0; d1 < 2; d1++)
                        if (d || d1)
                         F[t^1][d0][d] = min(F[t^1][d0][d], F[t][d0][d1] + (d ? f[cur] : g[cur]));
                    t ^= 1;
                }
                fx += min(F[t][1][1], F[t][1][0]);
                gx += F[t][0][1];
            }
        } else low[x] = min(low[x], pre[e[i].to]);
    }
    g[x] = min(gx, fx), f[x] = fx;
 }

int main() {
    scanf("%d%d",&n,&m);
    for(int i = 1; i <= m; i++) { int a, b; scanf("%d%d",&a,&b); ins(a, b), ins(b, a); }
    int ans = 0;
    for(int i = 1; i <= n; i++) if (!pre[i]) dfs(i,0), ans += g[i];
    printf("%d\n", ans);
    return 0;
}
























































