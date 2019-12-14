#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
int n, m;
int in_nextInt(){
  int xx;
  scanf("%d", &xx);
  return xx;
}


bool feasible(int*S, int k, int*A, int asz){
    int n = asz;
    bool M[n+1][k+1]; clr(M);
    M[0][0] = true;
    bool noWhite[n][n]; clr(noWhite);
    bool noBlack[n][n]; clr(noBlack);
    for(int i=0; i< n; i++){
        noWhite[i][i] = (A[i] >= 0);
        noBlack[i][i] = (A[i] <= 0);
        for (int j = i+1; j < n; j++){
            noWhite[i][j] = noWhite[i][j-1] && (A[j] >= 0);
            noBlack[i][j] = noBlack[i][j-1] && (A[j] <= 0);
        }
    }
    for(int i=1; i<=n; i++){
        if (A[i-1] == 1) 
            break;
        M[i][0] = true;
    }
    for(int j=1; j<=k; j++){
        for(int i = 1; i <= n; i++){
            bool a = M[i-1][j];
            bool b = (i >= S[j-1]) && noWhite[i-S[j-1]][i-1] && (((j == 1) && (i == S[j-1] || noBlack[0][i-S[j-1]-1] )) || ((i> S[j-1]) && noBlack[i-S[j-1]-1][i-S[j-1]-1] && M[i-S[j-1]-1][j-1]));
            M[i][j] = (a && A[i-1] <= 0) || (b && A[i-1] >= 0);
        }
    }
    return M[n][k];
}
bool checkForUpdates(int*S, int k, int*A, int asz){
    bool changed = false;
    int n = asz;
    for(int i = 0; i < n; i++){
        if (A[i] == 0) {
            A[i] = 1;
            if(!feasible(S, k, A, asz)){
                A[i] = -1;
                changed = true;
            }
            else{
                A[i] = -1;
                if(!feasible(S, k, A, asz)){
                    A[i] = 1;
                    changed = true;
                }
                else{
                    A[i] = 0;
                }
            }
        }
    }
    return changed;
}

int main(){
    n = in_nextInt();
    m = in_nextInt();
    int c = 1;
    int rl[n]; clr(rl);
    int cl[m]; clr(cl);
    int rows[n][m]; clr(rows);
    int cols[m][n]; clr(cols);
    for(int i = 0; i < n; i++){
        rl[i] = in_nextInt();
        for (int j = 0; j < rl[i]; j++){
            rows[i][j] = in_nextInt();
        }
    }
    for(int i = 0; i < m; i++){
        cl[i] = in_nextInt();
        for (int j = 0; j < cl[i]; j++){
            cols[i][j] = in_nextInt();
        }
    }
    int board[n][m]; clr(board);
    bool changed = true;
    while(changed){
        changed = false;
        for(int row = 0; row < n; row++){
            int R[m]; clr(R);
            for(int i = 0; i < m; i++){
                R[i] = board[row][i];
            }
            if(checkForUpdates(rows[row], rl[row], R, m)){
                changed = true;
                for(int i = 0; i < m; i++){
                    board[row][i] = R[i];
                }
            }
        }
        for(int col = 0; col < m; col++){
            int C[n]; clr(C);
            for(int i = 0; i < n; i++){
                C[i] = board[i][col];
            }
            if(checkForUpdates(cols[col], cl[col], C, n)){
                changed = true;
                for(int i = 0; i < n; i++){
                    board[i][col] = C[i];
                }
            }
        }
    }
void printBoard(){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            char c = '?';
            if(board[i][j] ==  1) c = 'X';
            if(board[i][j] == -1) c = '.';
            putchar(c);
        }
        puts("");
    }
}
    printBoard();
    c++;
    return 0;
}

