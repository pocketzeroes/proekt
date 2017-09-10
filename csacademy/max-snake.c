#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

enum{ N = 1000};
int a[N][N];
int main(){
    int T;
    scanf("%d", &T);
    while (T--){
        int n, m, x, y;
        scanf("%d %d %d %d", &n, &m, &x, &y);
        x--; y--;
        if (n * m % 2 == 1 && (x + y) % 2 == 1){
            puts("-1"); continue;
        }
        if (n % 2 == 0){
            int val = 0;
            for (int i = 0; i < n; i++)
                a[i][0] = val++;
            for (int i = n - 1; i > -1; i--){
                if (i % 2 == 1)
                    for (int j = 1; j < m; j++)
                        a[i][j] = val++;
                else
                    for (int j = m - 1; j > 0; j--)
                        a[i][j] = val++;
            }
            int d = a[x][y];
            for (int i = 0; i < n; i++)
                for (int j = 0; j < m; j++)
                    a[i][j] = (a[i][j] - d + n * m) % (n * m);
            for (int i = 0; i < n; i++){
                for (int j = 0; j < m; j++)
                    printf("%d ", a[i][j] + 1);
                puts("");
            }
            continue;
        }
        if (m % 2 == 0){
            int val = 0;
            for (int j = 0; j < m; j++)
                a[0][j] = val++;
            for (int j = m - 1; j > -1; j--){
                if (j % 2 == 1)
                    for (int i = 1; i < n; i++)
                        a[i][j] = val++;
                else
                    for (int i = n - 1; i > 0; i--)
                        a[i][j] = val++;
            }
            int d = a[x][y];
            for (int i = 0; i < n; i++)
                for (int j = 0; j < m; j++)
                    a[i][j] = (a[i][j] - d + n * m) % (n * m);
            for (int i = 0; i < n; i++){
                for (int j = 0; j < m; j++)
                    printf("%d ", a[i][j] + 1);
                puts("");
            }
            continue;
        }
        if (x % 2 == 1 && y % 2 == 1){
            int val = 0;
            for (int j = y; j > -1; j--)
                if (j % 2 == 0)
                    for (int i = 0; i < x + 1; i++)
                        a[i][j] = val++;
                else
                    for (int i = x; i > -1; i--)
                        a[i][j] = val++;
            for (int i = x + 1; i < n; i++)
                if (i % 2 == 0)
                    for (int j = 0; j < y + 1; j++)
                        a[i][j] = val++;
                else
                    for (int j = y; j > -1; j--)
                        a[i][j] = val++;
            for (int i = n - 1; i > -1; i--)
                if (i % 2 == 0)
                    for (int j = y + 1; j < m; j++)
                        a[i][j] = val++;
                else
                    for (int j = m - 1; j > y; j--)
                        a[i][j] = val++;
            for (int i = 0; i < n; i++){
                for (int j = 0; j < m; j++)
                    printf("%d ", a[i][j] + 1);
                puts("");
            }
            continue;
        }
        if (y == 0){
            int val = 0;
            for (int i = x; i > -1; i--)
                a[i][0] = val++;
            for (int i = 0; i < n; i++)
                if (i % 2 == 0)
                    for (int j = (i > x ? 0 : 1); j < m; j++)
                        a[i][j] = val++;
                else
                    for (int j = m - 1; j > (i > x ? -1 : 0); j--)
                        a[i][j] = val++;
            for (int i = 0; i < n; i++){
                for (int j = 0; j < m; j++)
                    printf("%d ", a[i][j] + 1);
                puts("");
            }
            continue;
        }
        else if (x == n - 1){
            int val = 0;
            for (int j = y; j > -1; j--)
                a[n - 1][j] = val++;
            for (int j = 0; j < m; j++)
                if (j % 2 == 0)
                    for (int i = (j > y ? n - 1 : n - 2); i > -1; i--)
                        a[i][j] = val++;
                else
                    for (int i = 0; i < (j > y ? n : n - 1); i++)
                        a[i][j] = val++;
            for (int i = 0; i < n; i++){
                for (int j = 0; j < m; j++)
                    printf("%d ", a[i][j] + 1);
                puts("");
            }
            continue;
        }
        else{
            int val = 0;
            for (int i = x; i > -1; i--)
                a[i][y] = val++;
            for (int i = 0; i < x + 1; i++)
                if (i % 2 == 0)
                    for (int j = y - 1; j > -1; j--)
                        a[i][j] = val++;
                else
                    for (int j = 0; j < y; j++)
                        a[i][j] = val++;
            for (int j = 0; j < y + 1; j++)
                if (j % 2 == 0)
                    for (int i = x + 1; i < n; i++)
                        a[i][j] = val++;
                else
                    for (int i = n - 1; i > x; i--)
                        a[i][j] = val++;
            for (int i = n - 1; i > -1; i--)
                if (i % 2 == 0)
                    for (int j = y + 1; j < m; j++)
                        a[i][j] = val++;
                else
                    for (int j = m - 1; j > y; j--)
                        a[i][j] = val++;
            for (int i = 0; i < n; i++){
                for (int j = 0; j < m; j++)
                    printf("%d ", a[i][j] + 1);
                puts("");
            }
            continue;
        }
    }
    return 0;
}


















































