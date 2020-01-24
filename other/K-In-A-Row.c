#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
char data[200][200];

int main(){
    int l;
    scanf("%d", &l);
    int xwin = 0;
    int owin = 0;
    for(; l > 0; --l){
        int m, n, r;
        scanf("%d%d%d", &m, &n, &r);
        getchar();
        for (int i = 0; i < n; ++i){
            for (int j = 0; j < m; ++j){
                data[i][j]=getchar();
            }
            getchar();
        }
        bool xx = false;
        bool oo = false;
        for (int i = 0; i < n; ++i){
            for (int j = 0; j < m - r + 1; ++j){
                char now = data[i][j];
                for (int k = 1; k < r; ++k){
                    if (data[i][j + k] != now)
                        now = '.';
                }
                if (now == 'x')
                    xx = true;
                if (now == 'o')
                    oo = true;
            }
        }
        for (int i = 0; i < n - r + 1; ++i){
            for (int j = 0; j < m; ++j){
                char now = data[i][j];
                for (int k = 1; k < r; ++k){
                    if (data[i + k][j] != now)
                        now = '.';
                }
                if (now == 'x')
                    xx = true;
                if (now == 'o')
                    oo = true;
            }
        }
        for (int i = 0; i < n - r + 1; ++i){
            for (int j = r - 1; j < m; ++j){
                char now = data[i][j];
                for (int k = 1; k < r; ++k){
                    if (data[i + k][j - k] != now)
                        now = '.';
                }
                if (now == 'x')
                    xx = true;
                if (now == 'o')
                    oo = true;
            }
        }
        for (int i = 0; i < n - r + 1; ++i){
            for (int j = 0; j < m - r + 1; ++j){
                char now = data[i][j];
                for (int k = 1; k < r; ++k){
                    if (data[i + k][j + k] != now)
                        now = '.';
                }
                if (now == 'x')
                    xx = true;
                if (now == 'o')
                    oo = true;
            }
        }
        xwin += xx;
        owin += oo;
    }
    printf("%d:%d\n", xwin, owin);
    return 0;
}
