#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
#include<assert.h>
#define swap(a,b) do\
    {\
      a ^= b;\
      b ^= a;\
      a ^= b;\
    } while (0)
        
typedef long long ll;
const double INF = 1e16;
enum{ N = 2010};
int n;
double a[N][N];
double b[N][2];
double dist[N];
bool used[N];
int par[N];
int ed[N][2];
int edSz;
int ans[N][2];
int ansSz;
int deg[N];
int revOrd[N];

double sqr(double x) {
    return x * x;
}
void read() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%lf%lf", &b[i][0], &b[i][1]);
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            a[i][j] = 0;
            for (int k = 0; k < 2; k++)
                a[i][j] += sqr(b[i][k] - b[j][k]);
            a[i][j] = sqrt(a[i][j]);
        }
}
void solve() {
    edSz = 0;
    for (int i = 0; i < n; i++)
        used[i] = 0;
    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        par[i] = -1;
    }
    dist[0] = 0;
    for (int it = 0; it < n; it++) {
        int v = -1;
        for (int i = 0; i < n; i++) {
            if (used[i]) 
                continue;
            if (v == -1 || dist[i] < dist[v])
                v = i;
        }
        used[v] = 1;
        if (par[v] != -1) {
            ed[edSz][0] = v;
            ed[edSz][1] = par[v];
            edSz++;
        }
        for (int u = 0; u < n; u++) {
            if (used[u]) 
                continue;
            if (a[v][u] < dist[u]) {
                dist[u] = a[v][u];
                par[u] = v;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        used[i] = 0;
        deg[i] = 0;
    }
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < 2; j++)
            deg[ed[i][j]]++;
    ansSz = 0;
    for (int it = 0; it < n - 1; it++) {
        int m = 0;
        for (int i = 0; i < n; i++)
            if (!used[i])
                revOrd[i] = m++;
        bool fnd = false;
        for (int i = 0; !fnd && i < n - 1; i++) {
            int v = ed[i][0], u = ed[i][1];
            if (used[v] || used[u]) 
                continue;
            if (deg[u] == 1) 
                swap(v, u);
            if (deg[v] > 1) 
                continue;
            int id1 = revOrd[v], id2 = revOrd[u];
            if (abs(id1 - id2) == 1 || abs(id1 - id2) == m - 1) {
                ans[ansSz][0] = v;
                ans[ansSz][1] = u;
                ansSz++;
                used[v] = 1;
                deg[u]--;
                fnd = true;
            }
        }
        if (!fnd) 
            assert(!"throw");
    }
    for (int i = 0; i < ansSz; i++)
        printf("%d %d\n", ans[i][0] + 1, ans[i][1] + 1);
}
int main() {
    int t;
    scanf("%d", &t);
    while(t--) {read(); solve();};
    return 0;
}
