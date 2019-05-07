#include <stdio.h>
#define MAXN (20)
#define MAXM (100)
#define LARGE (1e8)
int piv[MAXN];
int vis[MAXM];
int A[MAXN][MAXN];
int ned[MAXN];
int edges[MAXN][MAXM];
int dp[1<<MAXN][MAXN];
int vec[MAXM];
int n, m, l;
int fifo[MAXN*(1<<MAXN)][2];
int eq, dq;
#if SOL
int sp[1<<MAXN][MAXN][2];
#endif
int rk(int n,int m,int *v)
{
    int i,j;
    int rnk = 0;
    for (i = 0 ; i < n; i++) {
        piv[i] = -1;
    }
    for (i = 0 ; i < m; i++) {
        vis[i] = 0;
    }
    for (i = 0 ; i < n; i++) {
        for (j = 0; j < m; j++) {
            if (!vis[j] && v[j]&(1<<i)) {
                piv[i] = j;
            }
        }
        if (piv[i] != -1) {
            vis[piv[i]] = 1;
            rnk++;
            for (j = 0; j < m; j++) {
                if (j != piv[i] && v[j]&(1<<i)) {
                    v[j] ^= v[piv[i]];
                }
            }
        }
    }
    return rnk;
}
void solve()
{
    int i,j,k;
    for (i = 0; i < (1<<n); i++) {
        for (j = 0; j < n; j++) {
            dp[i][j] = LARGE;
        }
    }
    dp[2][1] = 1;
#if SOL
    sp[2][1][0] = -1;
#endif
    eq = dq = 0;
    fifo[eq][0] = 2;
    fifo[eq++][1] = 1;
    while (dq < eq) {
        int x = fifo[dq][0];
        int y = fifo[dq++][1];
        for (k = 0; k < n; k++) {
            if (k != y && A[y][k] && dp[x|(1<<k)][k] > dp[x][y] + 1) {
                dp[x|(1<<k)][k] = dp[x][y] + 1;
                fifo[eq][0] = x|(1<<k);
                fifo[eq++][1] = k;
#if SOL
                sp[x|(1<<k)][k][0] = x;
                sp[x|(1<<k)][k][1] = y;
#endif
            }
        }
    }
}
#if SOL
void print_sol(int w, int i)
{
    if (sp[w][i][0]>-1) {
        print_sol(sp[w][i][0],sp[w][i][1]);
    }
    printf(" %d", i);
}
#endif
int main(){
    int i, j, id, p, q, mrk;
    int best = LARGE;
#if SOL
    int bwho;
#endif
    scanf("%d %d %d",&n,&m,&l);
    for (i = 0;i < n; i++) {
        ned[i] = 0;
        for (j = 0;j < n ; j++)
            A[i][j] = 0;
    }
    for (i = 0; i < m; i++) {
        int t,f;
        scanf("%d %d",&t,&f);
        A[t][f] = 1;
        A[f][t] = 1;
    }
    for (i = 0;i < l; i++) {
        int sw = 0;
        scanf("%d %d",&id,&p);
        for (j = 0; j < p; j++) {
            scanf("%d",&q);
            sw ^= (1<<q);
        }
        edges[id][ned[id]++] = sw;
        vec[i] = sw;
    }
    mrk = rk(n,l,vec);
#if SOL
    printf("max rank = %d\n", mrk);
#endif
    solve();
    for (i = 0; i < (1<<(n-2)); i++) {
        if (dp[(i<<2)^3][0] < best) {
            int cnt = 0;
            for (j = 0;j < n; j++) {
                if (((i<<2)^3)&(1<<j)) {
                    int k;
                    for (k = 0;k < ned[j]; k++) {
                        vec[cnt++] = edges[j][k];
                    }
                }
            }
            if (rk(n, cnt, vec) == mrk) {
                best = dp[(i<<2)^3][0];
#if SOL
                bwho = (i<<2)^3;
#endif
            }
        }
    }
    printf("%d\n",best);
#if SOL
    printf("Solution: ");
    print_sol(bwho,0);
    printf("\n");
#endif
    return 0;
}
