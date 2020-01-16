#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ maxn = 505   };
enum{ INF = 9999999};

static inline int getint(){
    int ans=(0);
    char w = getchar();
    while(w < '0' || w > '9')
        w = getchar();
    while('0' <= w && w <= '9'){
        ans = ans * 10 + w - '0';
        w = getchar();
    }
    return ans;
}
static inline int max(int a, int b){return a > b ? a : b;}
static inline int min(int a, int b){return a < b ? a : b;}
int n;
int a    [maxn];
int count[maxn], count2[maxn];
int sum  [maxn];
int exist[maxn];
int g    [maxn][maxn];
int f    [maxn];


static inline int check(int l, int r){
    memset(exist, 0, sizeof exist);
    for(int i = l; i <= r; ++i)
        if(exist[a[i]])
            return false;
    else
        ++exist[a[i]];
    for(int i = 1; i <= r - l + 1; ++i)
        if(!exist[i])
            return false;
    return true;
}
int main(){
    n = getint();
    for(int i = 1; i <= n; ++i)
        a[i] = getint();
    memset(g, 0x7F, sizeof g);
    for(int i = n; i; --i){
        g[i][i] = 0;
        for(int j = i + 1; j <= n; ++j){
            g[i][j] = INF;
            int Max=(0),
               flag=(0),
               Min1=(INF),
               Min2=(INF),
               ans=(INF),
               Min=(INF);
            memset(count2, 0, sizeof count2);
            memset(count, 0, sizeof count);
            for(int w = i; w <= j; ++w)
                if(count2[a[w]]){
                    flag = 1;
                    break;
                }
                else{
                    ++count2[a[w]];
                    ++count[a[w]];
                    Min2 = min(Min2, a[w]);
                    Max = max(Max, a[w]);
                }
            if(flag)
                continue;
            sum[Min2 - 1] = 0;
            for(int w = Min2; w <= Max; ++w)
                sum[w] = sum[w - 1] + count[w];
            for(int k = i; k < j; ++k){
                --count2[a[k]];
                Min1 = min(Min1, a[k]);
                if(Min2 == a[k])
                    for(Min2; !count2[Min2]; ++Min2);
                ans = min(ans, g[i][k] + g[k + 1][j] + (j - i + 1) - sum[max(Min1, Min2) - 1]);
            }
            g[i][j] = ans;
        }
    }
    f[0] = 0;
    for(int i = 1; i <= n; ++i)
        f[i] = INF;
    if(a[1] == 1)
        f[1] = 0;
    for(int i = 2; i <= n; ++i){
        for(int j = 0; j < i; ++j)
            if(check(j + 1, i)){
                f[i] = min(f[i], f[j] + g[j + 1][i]);
            }
    }
    if(f[n] != INF)
        printf("%d\n", f[n]);
    else
        printf("Impossible\n");
    return 0;
}
