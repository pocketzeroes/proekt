#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long double ld;
enum{ MAXN = 501};
bool done[MAXN][MAXN][MAXN];
ld   dp  [MAXN][MAXN][MAXN];

inline int nc2(int x){
    return x * (x - 1) / 2;
}
ld solve(int x, int y, int z){
    if(x == 0 && z <= 1)
        return 1.0;
    if(done[x][y][z])
        return dp[x][y][z];
    int socks = 2 * x + y + z;
    int total = nc2(socks);
#define res dp[x][y][z]
    res = 0.0;
    if(x >= 2          ){ int ways = nc2(2 * x) - x; res += ways * solve(x - 2, y + 2, z) / total;}
    if(x >= 1 && y >= 1){ int ways = 2 * x * y;      res += ways * solve(x - 1, y, z)     / total;}
    if(x >= 1 && z >= 1){ int ways = 2 * x * z;      res += ways * solve(x-1,y+1,z - 1)   / total;}
    if(y >= 2          ){ int ways = nc2(y);         res += ways * solve(x, y - 2, z)     / total;}
    if(y >= 1 && z >= 1){ int ways = y * z;          res += ways * solve(x, y - 1, z - 1) / total;}
    done[x][y][z] = true;
    return res;
}
int main(){
    int x, y;
    scanf("%d %d", &x, &y);
    printf("%.13Lf\n", solve(x, 0, y) );
    return 0;
}
