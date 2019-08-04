#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ maxn = 10};
int N,n,point[maxn][maxn];
char Data[maxn][maxn];
bool link[maxn][maxn][maxn][maxn];
bool vis[maxn][maxn];
int dx[] = { 1, 1, -1, -1 };
int dy[] = { -1, 1, 1, -1 };
bool found;

void Loop(int nx,int ny,int f_x,int f_y){
    if (found || nx<0 || nx>n || ny<0 || ny>n || !link[nx][ny][f_x][f_y]) 
        return;
    if (vis[nx][ny]){
        found = true;
        return;
    }
    vis[nx][ny] = true;
    for (int i = 0; i < 4; i++){
        int newx = nx + dx[i];
        int newy = ny + dy[i];
        if (newx!=f_x||newy!=f_y)
            Loop(newx, newy,nx,ny);
    }
}
bool exist(int curx,int cury){
    found = false;
    memset(vis, 0, sizeof(vis));
    vis[curx][cury] = true;
    Loop(curx + 1, cury + 1,curx,cury);
    Loop(curx - 1, cury - 1,curx,cury);
    Loop(curx + 1, cury - 1,curx,cury);
    Loop(curx - 1, cury + 1,curx,cury);
    return found;
}
bool dfs(int row,int col){
    if (col == n){
        if (Data[row][col] != '.'&&point[row][col] != Data[row][col] - '0')
            return false;
        row++; col = 0;
        if (row == n){
            for (int j = 0; j <= n; j++){
                if (Data[row][j] != '.'&&point[row][j] != Data[row][j] - '0')
                    return false;
            }
            return true;
        }
        else{
            if (dfs(row,col))
                return true;
            return false;
        }
    }
    int curx = row, cury = col;
    point[curx][cury]++;
    point[curx + 1][cury + 1]++;
    link[curx][cury][curx + 1][cury + 1] = true;
    link[curx + 1][cury + 1][curx][cury] = true;
    if (Data[curx][cury] != '.'&&point[curx][cury] != Data[curx][cury] - '0'){
    }
    else if (Data[curx + 1][cury + 1] != '.'&&point[curx + 1][cury + 1] > Data[curx + 1][cury + 1] - '0'){
    }
    else if (!exist(curx,cury)){
        col++;
        if (dfs(row, col)) 
            return true;
        col--;
    }
    point[curx][cury]--;
    point[curx + 1][cury + 1]--;
    link[curx][cury][curx + 1][cury + 1] = false;
    link[curx + 1][cury + 1][curx][cury] = false;
    point[curx][cury + 1]++;
    point[curx + 1][cury]++;
    link[curx][cury+1][curx+1][cury] = true;
    link[curx+1][cury][curx][cury+1] = true;
    if (Data[curx][cury+1] != '.'&&point[curx][cury+1] > Data[curx][cury+1] - '0'){
    }
    else if (Data[curx + 1][cury] != '.'&&point[curx + 1][cury] > Data[curx + 1][cury] - '0'){
    }
    else if (Data[curx][cury]!='.'&&point[curx][cury]!=Data[curx][cury]-'0'){
    }
    else if (!exist(curx, cury+1)){
        col++;
        if (dfs(row, col)) 
            return true;
        col--;
    }
    point[curx][cury + 1]--;
    point[curx + 1][cury]--;
    link[curx][cury + 1][curx + 1][cury] = false;
    link[curx + 1][cury][curx][cury + 1] = false;
    return false;
}
int main(){
    N=1;
    while (N--){
        scanf("%d", &n);
        getchar();
        for (int i = 0; i <= n; i++){
            for (int j = 0; j <= n; j++){
                Data[i][j]=getchar();
            }
            getchar();
        }
        memset(link , 0, sizeof(link) );
        memset(point, 0, sizeof(point));
        memset(vis  , 0, sizeof(vis)  );
        dfs(0, 0);
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                if (point[i][j] &&point[i+1][j+1]&& link[i][j][i + 1][j + 1]){
                    putchar('\\');
                }
                else
                    putchar('/');
            }
            puts("");
        }
    }
    return 0;
}
