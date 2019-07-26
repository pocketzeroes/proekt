#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
enum{ inf = 0x3f3f3f3f};
enum{ maxn = 1005     };
int a   [105][105], 
    l   [105][105], 
    r   [105][105];
int leap[505][505], 
    vis [505], 
    g   [505], x, y, numl, numr;

bool find(int x){
    int i, j;
    for (j = 1; j <= numr; j++){
        if (leap[x][j] && !vis[j]){
            vis[j] = 1;
            if (g[j] == 0 || find(g[j])){
                g[j] = x;
                return true;
            }
        }
    }
    return false;
}
int main(){
    int i, j, m, n, ans, t;
    scanf("%d", &t);
    while(t--){
        scanf("%d %d", &y, &x);
        memset(a, 0, sizeof(a));
        memset(l, 0, sizeof(l));
        memset(r, 0, sizeof(r));
        memset(leap, 0, sizeof(leap));
        int c;
        scanf("%d", &c);
        for (i = 1; i <= c; i++){
            scanf("%d %d", &m, &n);
            a[m][n] = 1;
        }
        scanf("%d", &c);
        for (i = 1; i <= c; i++){
            scanf("%d %d", &m, &n);
            a[m][n] = 2;
        }
        int cnt = 1, flag1, flag2;
        for (i = 1; i <= y; i++){
            flag1 = flag2 = 0;
            for (j = 1; j <= x; j++){
                if (a[i][j] == 1&&!flag2){
                    flag1   = 1;
                    l[i][j] = cnt;
                    numl    = cnt;
                }
                else if (a[i][j] == 1){
                    cnt++;
                    numl    = cnt;
                    l[i][j] = cnt;
                    flag2   = 0;
                }
                else if (a[i][j] == 2 && flag1)
                    flag2 = 1;
            }
            if (flag1)
                cnt++;
        }
        cnt = 1;
        for (j = 1; j <= x; j++){
            flag1 = flag2 = 0;
            for (i = 1; i <= y; i++){
                if (a[i][j] == 1&&!flag2){
                    flag1   = 1;
                    r[i][j] = cnt;
                    numr    = cnt;
                }
                else if (a[i][j] == 1){
                    cnt++;
                    numr    = cnt;
                    r[i][j] = cnt;
                    flag2   = 0;
                }
                else if (a[i][j] == 2 && flag1)
                    flag2 = 1;
            }
            if (flag1)
                cnt++;
        }
        for (i = 1; i <= y; i++)
            for (j = 1; j <= x; j++)
                if (l[i][j] && r[i][j])
                    leap[l[i][j]][r[i][j]] = 1;
        memset(g, 0, sizeof(g));
        ans = 0;
        for (i = 1; i <= numl; i++){
            memset(vis, 0, sizeof(vis));
            if (find(i))
                ans++;
        }
        printf("%d\n", ans);
    }
    return 0;
}
