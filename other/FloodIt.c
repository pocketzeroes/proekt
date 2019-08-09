#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
enum{ max_colors = 6};
int n, seen;
int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
enum{MAXN=20};

typedef struct{
    char arr[MAXN][MAXN];
}mat;

mat board;
mat mark;

void floodfill(char c, int i, int j){
    if(i < 0 || i >= n || j < 0 || j >= n)
        return;
    if(board.arr[i][j] != c)
        return;
    if(mark.arr[i][j])
        return;
    seen++;
    mark.arr[i][j] = 1;
    for(int k = 0; k < 4; k++)
        floodfill(c, i + dir[k][0], j + dir[k][1]);
    return;
}
int main(){
    int tn;
    for(scanf("%d", &tn); tn--;){
        scanf("%d", &n);
        getchar();
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                board.arr[i][j] = getchar();
            }
            getchar();
        }
        mat connected;
        seen = 0;
        floodfill(board.arr[0][0], 0, 0);
        connected = mark;
        int totalMoves = 0;
        int moves[max_colors]; memset(moves, 0, sizeof(moves));
        int maxConnected = seen;
        while (maxConnected < n * n){
            maxConnected = 0;
            int maxdex = -1;
            mat maxMark;
            for (int k = 1; k <= max_colors; k++){
                for (int i = 0; i < n; i++)
                    for (int j = 0; j < n; j++)
                        if (connected.arr[i][j])
                            board.arr[i][j] = '0' + k;
                seen = 0;
                memset(mark.arr, 0, sizeof(mark.arr));
                floodfill('0' + k, 0, 0);
                if(seen > maxConnected){
                    maxConnected = seen;
                    maxdex = k;
                    maxMark = mark;
                }
            }
            totalMoves++;
            moves[maxdex - 1]++;
            connected = maxMark;
        }
        printf("%d\n", totalMoves);
        for (int i = 0; i < max_colors; i++){
            if (i > 0)
                printf(" ");
            printf("%d", moves[i]);
        }
        puts("");
        memset(mark.arr, 0, sizeof(mark.arr));
    }
    return 0;
}