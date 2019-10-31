#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ MAXD  = 100};
enum{ FOUND = 0  };
enum{ STOP  = 1  };
enum{ FILL  = 2  };

char grid[MAXD][MAXD], 
     save[MAXD][MAXD];
char*labels = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
int ilabel = 0;

void printGrid(int n, int m){
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            putchar(grid[i][j]);
        }
        puts("");
    }
}
int check(int r, int c, int sze, bool found, int nRows, int nCols){
    if (r+sze-1 >= nRows || c+sze-1 >= nCols)
        return STOP;
    int retVal = FILL;
    for(int i=r; i<r+sze; i++) {
        switch (grid[i][c+sze-1]){
          case '$' : if (found) return STOP; retVal = FOUND;
          case '.' : break;
          default : return STOP;
        }
    }
    for(int j=c; j<c+sze-1; j++) {
        switch (grid[r+sze-1][j]) {
          case '$' : if (found) return STOP; retVal = FOUND;
          case '.' : break;
          default : return STOP;
        }
    }
    return retVal;
}
int fillShell(int r, int c, int sze, char label){
    for(int i=r; i<r+sze; i++) {
        grid[i][c+sze-1] = label;
    }
    for(int j=c; j<c+sze-1; j++) {
        grid[r+sze-1][j] = label;
    }
    return FILL;
}
void unfill(int r, int c, int sze){
    for(int i=r; i<r+sze; i++)
        for(int j=c; j<c+sze; j++)
            grid[i][j] = save[i][j];
}
bool fillGrid(int r, int c, int iLabel, int nRows, int nCols){
    while (r < nRows && grid[r][c] != '.' && grid[r][c] != '$') {
        c++;
        if (c == nCols) {
            r++;
            c = 0;
        }
    }
    if (r == nRows)
        return true;
    char label = labels[iLabel];
    int sqSize = 1;
    bool found = false;
    int ans = check(r, c, sqSize, found, nRows, nCols);
    while (ans == FILL) {
        fillShell(r, c, sqSize, label);
        ans = check(r, c, ++sqSize, found, nRows, nCols);
    }
    if (ans == STOP) {
        unfill(r, c, sqSize-1);
        return false;
    }
    found = true;
    do {
        fillShell(r, c, sqSize, label);
        if (fillGrid(r, c, iLabel+1, nRows, nCols))
            return true;
        ans = check(r, c, ++sqSize, found, nRows, nCols);
    }
    while (ans == FILL);
    unfill(r, c, sqSize-1);
    return false;
}
int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    getchar();
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            grid[i][j] = getchar();
            save[i][j] = grid[i][j];
        }
        getchar();
    }
    if(!fillGrid(0, 0, 0, n, m))
        puts("elgnatcer");
    else
        printGrid(n, m);
    return 0;
}
