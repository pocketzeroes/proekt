#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}


int n, m, k;
int a[10][10];
int dp[2][1 << 14][10][10];
int age[101];
int dx[4] = {1, 0, 0, -1};
int dy[4] = {0, 1, -1, 0};
int history[10][10];

int main(){
    scanf("%d %d %d", &n, &m, &k);
    for (int i=0; i<n; i++)
        for (int j=0; j<m; j++)
            scanf("%d", &a[i][j]);
    for (int i=1; i<=100; i++)  age[i] = age[i/2] + 1;
    for (int i=1; i<=100; i++)  age[i]++;
    for (int i=1; i<=100; i*=2) age[i]--;
    dp[1][0x1111][0][0] = a[0][0];
    for (int vreme=2; vreme<=k; vreme++){
#define ol dp[1 - vreme % 2]
#define nu dp[vreme%2]
        memset(nu, 0, sizeof(dp[0]));
        for(int mask=0; mask<(1 << 14); mask++){
            {
                int t = mask ^ (mask >> 2);
                t &= 0xfff;
                t = t & (t >> 1);
                if (t & 0x555555)
                    continue;
            }
            for(int x=0; x<n; x++){
                for(int y=0; y<m; y++){
                    if(ol[mask][x][y] == 0)
                        continue;
                    int fx = x, fy = y;
                    for(int b=0; b<7; b++){
                        int deo = 3 & (mask >> (2*b));
                        fx -= dx[deo];
                        fy -= dy[deo];
                        if(0 <= fx && fx < n && 0 <= fy && fy < m)
                            history[fx][fy] = b + 1;
                    }
                    for(int dir=0; dir<4; dir++){
                        int nx = x + dx[dir];
                        int ny = y + dy[dir];
                        if(!(0 <= nx && nx < n && 0 <= ny && ny < m))
                            continue;
                        if(history[nx][ny] && history[nx][ny] < age[a[nx][ny]])
                            continue;
                        int numask = ((mask << 2) + dir) & ((1 << 14) - 1);
#define v nu[numask][nx][ny]
                        v = max(v, ol[mask][x][y] + a[nx][ny]);
                    }
                    memset(history, 0, sizeof(history));
                }
            }
        }
    }
    int sol = 0;
    for (int x=0; x<n; x++)
        for (int y=0; y<m; y++)
            for (int mask=0; mask < (1<< 14); mask++)
                sol = max(sol, dp[k % 2][mask][x][y]);
    printf("%d\n", sol);
}
