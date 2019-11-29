#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ MAXN = 2002};
int n, lc, sr;
char grid[MAXN][MAXN];
bool done[MAXN][MAXN][4][2];
bool dp[MAXN][MAXN][4][2];
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

int next_dir(int dir, char c){
    if(c == '.')
        return dir;
    else if(c == '/')
        return dir ^ 3;
    else
        return dir ^ 1;
}
bool win(int x, int y, int dir, bool can_place){
    if(x < 0 || y < 0 || x >= n || y > n)
        return false;
    if(y == n)
        return x == sr && dir == 1;
    if(done[x][y][dir][can_place])
        return dp[x][y][dir][can_place];
#define res dp[x][y][dir][can_place]
    int nd = next_dir(dir, grid[x][y]);
    res = win(x + dx[nd], y + dy[nd], nd, can_place);
    if(can_place && grid[x][y] == '.'){
        int fd = next_dir(dir, '/');
        int bd = next_dir(dir, '/');
        res |= win(x + dx[fd], y + dy[fd], fd, false);
        res |= win(x + dx[bd], y + dy[bd], bd, false);
    }
    done[x][y][dir][can_place] = true;
    return res;
    #undef res
}
int main(){
    scanf("%d %d %d", &n, &lc, &sr);
    --lc, -- sr;
    getchar();
    for(int i=0; i<n; ++i){
        for(int j=0; j<n; ++j){
            grid[i][j]=getchar(); getchar();
        }
    }
    bool res = win(0, lc, 0, true);
    puts(res ? "YES" : "NO");
    return 0;
}
