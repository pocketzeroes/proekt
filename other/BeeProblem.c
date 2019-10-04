#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ N=(int)1e3+100};
char maze[N][N];
int ans[N*N];
int cnt;
int h,n,m;
const int b1[6][2]={0,1,0,-1,1,0,-1,0,-1,-1,1,-1};
const int b2[6][2]={0,1,0,-1,1,0,-1,0,1,1,-1,1};
int num;

void dfs(int x,int y){
    num++;
    maze[x][y]='#';
    for(int k=0;k<6;k++){
        int xx,yy;
        if(x&1){
            xx=x+b2[k][0];
            yy=y+b2[k][1];
        }
        else{
            xx=x+b1[k][0];
            yy=y+b1[k][1];
        }
        if(xx<0||yy<0||xx>=n||yy>=m)
            continue;
        if(maze[xx][yy]=='#')
            continue;
        dfs(xx, yy);
    }
}
int cmp(const void*b, const void*a){ return ( *(int*)a - *(int*)b ); }
int main(){
    scanf("%d%d%d", &h, &n, &m);
    cnt = 0;
    getchar();
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            maze[i][j] = getchar();
            if(maze[i][j]==' ')
               maze[i][j] = getchar();
        }
        getchar();
    }
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++){
            if(maze[i][j]=='.'){
                num=0;
                dfs(i,j);
                ans[cnt++]=num;
            }
        }
    qsort(ans, cnt, sizeof(int), cmp);
    int temp = 0;
    int tem  = 0;
    int t    = 0;
    while(tem<h&&t<cnt){
        temp++;
        tem+=ans[t++];
    }
    printf("%d\n", temp);
    return 0;
}
