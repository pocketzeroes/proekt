#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int dl[20][100010], dr[20][100010];
int L[100010], R[100010];

int query(int d[][100010], int l, int r, int maxx){
    int t = log2(r - l + 1);
    if (maxx)
        return fmax(d[t][l], d[t][r - (1 << t) + 1]);
    return fmin(d[t][l], d[t][r - (1 << t) + 1]);
}
void init(int d[][100010], int a[], int len, int maxx){
    for (int i = 0; i < len; i++)
        d[0][i] = a[i];
    int t = 1;
    for (int i = 1; t <= len; i++){
        for (int j = 0; j + t < len; j++)
            if (maxx)
                d[i][j] = fmax(d[i - 1][j], d[i - 1][j + t]);
            else
                d[i][j] = fmin(d[i - 1][j], d[i - 1][j + t]);
        t <<= 1;
    }
}
int main(){
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d%d", &L[i], &R[i]);
    init(dl, L, n, 1);
    init(dr, R, n, 0);
    int ans = 1;
    for (int i = 1; i <= n; i++){
        int l = ans, r = n - i + 1;
        while (l <= r){
            int mid = l + r >> 1;
            if (query(dr, i - 1, i + mid - 2, 0) - query(dl, i - 1, i + mid - 2, 1) + 1 >= mid){
                ans = fmax(ans, mid); l = mid + 1;
            }
            else
                r = mid - 1;
        }
    }
    printf("%d\n", ans);
    return 0;
}
