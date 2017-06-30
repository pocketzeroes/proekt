#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

enum{ kMaxN =(int) 1e3 + 1};

int matrix[kMaxN][kMaxN];
int line_sum[kMaxN], col_sum[kMaxN];

int main() {
    int n; 
    scanf("%d", &n);
    for (int i = 0; i < n; i += 1) {
        for (int j = 0; j < n; j += 1){
            scanf("%d", &matrix[i][j]);
            line_sum[i] += matrix[i][j];
            col_sum [j] += matrix[i][j];
        }
    }
    int mx = 0;
    for (int i = 0; i < n; i += 1){
        mx = max(mx, line_sum[i]);
        mx = max(mx, col_sum [i]);
    }
    line_sum[n] = col_sum[n] = -1;
    int line = 0;
    int col  = 0;
    while (1) {
        if (line_sum[line] == mx) {
            line++;
        }
        if (col_sum[col] == mx) {
            col++;
        }
        if (line == n) {
            break;
        }
        int val = mx - max(line_sum[line], col_sum[col]);
        matrix[line][col] += val;
        line_sum   [line] += val;
        col_sum    [col ] += val;
    }
    for (int i = 0; i < n; i += 1) {
        for (int j = 0; j < n; j += 1) {
            printf("%d ", matrix[i][j] );
        }
        puts("");
    }
}










