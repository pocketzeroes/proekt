#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
ll min(ll a, ll b){return a<b?a:b;}
ll max(ll a, ll b){return a>b?a:b;}


enum{ N=100000};
enum{ MAX_NUM=9187201950435737471};
ll  dp[2][2][2][N];
int v [2][N];
int m;

void rec(int x, int y, int pl, bool vdu){
    ll mx = MAX_NUM;
    if(y+1 < m && dp[pl^1][0][x][y+1] == MAX_NUM){
        rec(x,y+1,pl^1,0);
    }
    if(y+1 < m)
        mx = dp[pl^1][0][x][y+1];
    if(!vdu && (x != 1 || y != m-1)){
        if(dp[pl^1][1][x^1][y] == MAX_NUM){
            rec(x^1,y,pl^1,1);
        }
        if(mx == MAX_NUM){
            mx = dp[pl^1][1][x^1][y];
        }
        else
            mx = (pl?min(mx,dp[pl^1][1][x^1][y]):max(mx,dp[pl^1][1][x^1][y]));
    }
    if(mx == MAX_NUM) 
        mx = 0;
    dp[pl][vdu][x][y] = mx+v[x][y];
}
int main(){
    scanf("%d", &m);
    for(int x=0; x<2; ++x){
        for(int i=0; i<m; ++i){
            scanf("%d", &v[x][i]);
        }
    }
    memset(dp, 127, sizeof dp);
    rec(0, 0, 1, 0);
    printf("%lld\n", dp[1][0][0][0]);
    return 0;
}
