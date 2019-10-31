#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ MAXD = 500+2  };
enum{ MAXELEV = 1000};
enum{ INF = 1000000 };

long grid  [MAXD][MAXD];
bool isPass[MAXD][MAXD];
long tab1  [MAXD][MAXD],
     tab2  [MAXD][MAXD];



bool checkForPass(int r, int c){
    int val = grid[r][c];
    if (val == INF || grid[r-1][c] == INF || grid[r+1][c] == INF)
        return false;
    if (grid[r-1][c] <= val || grid[r+1][c] <= val)
        return false;
    return (grid[r][c-1] < val && grid[r][c+1] < val);
}
void initTab1(int r, int c){
    for(int i=1; i<=r; i++)
        tab1[i][c] = grid[i][c];
    for(int j=c-1; j>=1; j--) {
        for(int i=1; i<=r; i++) {
            if (isPass[i][j])
                tab1[i][j] = INF;
            else {
                long tmp = fminl(tab1[i-1][j+1], tab1[i][j+1]);
                tab1[i][j] = grid[i][j] + fminl(tmp, tab1[i+1][j+1]);
            }
        }
    }
}
void nextPass(long tab[][MAXD], long tprev[][MAXD], int r, int c){
    for(int i=1; i<=r; i++)
        tab[i][c] = INF;
    for(int j=c-1; j>=1; j--) {
        for(int i=1; i<=r; i++) {
            if (isPass[i][j]) {
                long tmp = fminl(tprev[i-1][j+1], tprev[i][j+1]);
                tab[i][j] = grid[i][j] + fminl(tmp, tprev[i+1][j+1]);
            }
            else {
                long tmp = fminl(tab[i-1][j+1], tab[i][j+1]);
                tab[i][j] = grid[i][j] + fminl(tmp, tab[i+1][j+1]);
            }
        }
    }
}
long minFirstColumn(long t[][MAXD], int r){
    long ans = t[1][1];
    for(int i=2; i<=r; i++)
        ans = fminl(ans,t[i][1]);
    return ans;
}
int main(){
    int r, c, npasses;
    scanf("%d %d %d", &r, &c, &npasses);
    for(int i=0; i<=r+1; i++) {
        grid[i][0  ] = tab1[i][0  ] = tab2[i][0  ] = INF;
        grid[i][c+1] = tab1[i][c+1] = tab2[i][c+1] = INF;
    }
    for(int j=0; j<=c+1; j++) {
        grid[0][j  ] = tab1[0][j  ] = tab2[0][j  ] = INF;
        grid[r+1][j] = tab1[r+1][j] = tab2[r+1][j] = INF;
    }
    for(int i=1; i<=r; i++) {
        for(int j=1; j<=c; j++) {
            scanf("%ld", &grid[i][j]);
            if (grid[i][j] == -1)
                grid[i][j] = INF;
        }
    }
    for(int i=2; i<r; i++) {
        for(int j=2; j<c; j++) {
            isPass[i][j] = checkForPass(i,j);
        }
    }
    initTab1(r, c);
    for(int i=1; i<=npasses; i++) {
        if (i%2 == 1) {
            nextPass(tab2, tab1, r, c);
        }
        else {
            nextPass(tab1, tab2, r, c);
        }
    }
    long ans;
    if (npasses%2 == 1) {
        ans = minFirstColumn(tab2, r);
    }
    else {
        ans = minFirstColumn(tab1, r);
    }
    if (ans >= INF)
        puts("impossible");
    else
        printf("%ld\n", ans);
    return 0;
}
