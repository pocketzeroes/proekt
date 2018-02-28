#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

#define F first
#define S second
#define mp newPair
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
enum{ N = 523}; 
int n, m;
int  a [N][N];
int  dp[N][N];
pair pr[N][N];

pair get(int i, int j){
    if (i == pr[i][j].F && j == pr[i][j].S) 
        return mp(i, j);
    return pr[i][j] = get(pr[i][j].F, pr[i][j].S);
}
int main(){
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= m; j ++) {
            scanf("%d", &a[i][j]);
            pr[i][j] = mp(i, j);
        }
    }
    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= m; j ++) {
            pair mn = mp(i, j);
            for (int c5 = -1; c5 < 2; c5 ++) {
                for (int c6 = -1; c6 < 2; c6 ++) {
                    int ni = i + c5, nj = j + c6;
                    if(ni <= 0 || nj <= 0 || ni > n || nj > m)
                        continue;
                    if (a[ni][nj] < a[mn.F][mn.S])
                        mn = mp(ni, nj);
                }
            }
            pr[i][j] = mn;
        }
    }
    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= m; j ++) {
            pair now = get(i, j);
            dp[now.F][now.S] ++;
        }
    }
    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= m; j ++)
            printf("%d ", dp[i][j]);
        puts("");
    }
}
