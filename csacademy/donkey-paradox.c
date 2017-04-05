#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>



int main() {
    int n, m;
    int x1, y1, x2, y2;
    scanf("%d %d", &n , &m );
    scanf("%d %d", &x1, &y1);
    scanf("%d %d", &x2, &y2);
    int starveCells = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (abs(i - x1) + abs(j - y1) == abs(i - x2) + abs(j - y2)) {
                starveCells++;
            }
        }
    }
    printf("%d", starveCells);
}

