#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int main() {
    int h, w, x, y;
    scanf("%d %d %d %d", &h, &w, &x, &y);
    int res[h][w];
    int tmp;
    for (int i = 0; i < h; ++i){
        for (int j = 0; j < w; ++j){
            scanf("%d", &res[i][j]);
            if (i >= x && j >= y) 
                res[i][j] -= res[i - x][j - y];
        }
        for(int j = w; j < w + y; ++j)
            scanf("%d", &tmp);
    }
    for(int i = 0; i < h; ++i){
        for(int j = 0; j < w; ++j){
            printf("%d ", res[i][j]);
        }
        puts("");
    }
    return 0;
}
