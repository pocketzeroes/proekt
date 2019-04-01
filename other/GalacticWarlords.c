#include <stdio.h>

enum{ MAX = 1000};

int main() {
    int n, w, i, j, d, x[MAX], y[MAX], X[MAX], Y[MAX], D[MAX];
    scanf("%d %d", &w, &n);
    for (i = 0; i < n; i++){
        scanf("%d %d %d %d", x + i, y + i, X + i, Y + i);
        D[i] = 0;
    }
    d = 0;
    for (i = 0; i < n; i++){
        for (j = 0; j < i; j++){
            if ((x[i] - X[i]) * (y[j] - Y[j]) - (x[j] - X[j]) * (y[i] - Y[i]))
                d = 1;
            else if (!((x[i] - X[i]) * (y[j] - Y[i]) - (x[j] - X[i]) * (y[i] - Y[i])))
                D[j] = 1;
        }
    }
    for (i = 0; i < n; i++)
        n -= D[i];
    printf("%d\n", n + (d ? n : 1) < w ? ((w + 1 - 2 * n) / 2 < 1 ? 1 : (w + 1 - 2 * n) / 2) : 0);
    return 0;
}
