#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

inline int min(int a,int b){return a<b?a:b;}
inline int max(int a,int b){return a>b?a:b;}

enum{ MAX_N = 1000};

int n, m;
int a[MAX_N + 1][MAX_N + 1];
int w[MAX_N + 1][MAX_N + 1], h[MAX_N + 1][MAX_N + 1];
int s[MAX_N + 1][MAX_N + 1];

void read() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j){
            scanf("%d", &a[i][j]);
        }
    }
}
int getSum(int i, int j, int width, int height) {
    int res = s[i][j];
    if (j > width) { res -= s[i][j - width]; }
    if (i > height) { res -= s[i - height][j]; }
    if (j > width && i > height) { res += s[i - height][j - width]; }
    return res;
}
int main() {
    read();
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            s[i][j] = a[i][j] + s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (a[i][j] == 0) {
                w[i][j] = h[i][j] = 0;
                continue;
            }
            w[i][j] = 1 + w[i][j - 1];
            h[i][j] = 1 + h[i - 1][j];
        }
    }
    int best = -1;
    for (int i = 2; i < n; ++i) {
        for (int j = 2; j < m; ++j) {
            int width = w[i][j], height = h[i][j];
            if (width == 0 || width == j) 
                continue;
            if (height == 0 || height == i) 
                continue;
            int area = width * height;
            if (getSum(i, j, width, height) == area && 
                getSum(i + 1, j + 1, width + 2, height + 2) == area) {
                    best = max(best, width * height);
                }
        }
    }
    printf("%d", best);
}



















































