#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int matrix[n][m];
    for(int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j) {
            scanf("%d", &matrix[i][j]);
        }
    }
    for (int i = 0; i < n; ++i) {
        if (matrix[i][0] == 0) {
            for (int j = 0; j < m; ++j) {
                matrix[i][j] = 1 - matrix[i][j];
            }
        }
    }
    for (int j = 1; j < m; ++j) {
        int count = 0;
        for (int i = 0; i < n; ++i) {
            count += matrix[i][j];
        }
        if (count <= n / 2) {
            for (int i = 0; i < n; ++i) {
                matrix[i][j] = 1 - matrix[i][j];
            }
        }
    }
    long long res = 0;
    for (int j = 0; j < m; ++j) {
        int count = 0;
        for (int i = 0; i < n; ++i) {
            count += matrix[i][j];
        }
        res += count * 1LL << (m - j - 1);
    }
    printf("%lld\n", res);
}












