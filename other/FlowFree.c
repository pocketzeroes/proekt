#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ MAXN=(int)1e6+5};
enum{ P=99991   };
enum{ N = 5     };
typedef long long ll;
char s [N][N];
int vis[N][N];
int dir[4][2]= {1,0,-1,0,0,1,0,-1};
int num,flag=0;

int judge(int x, int y){
    if(0<=x && x<4 && 0<=y && y<4)
        return 0;
    return 1;
}
void DFS(int x, int y, char ch){
    if(s[x][y]!='W' && s[x][y]!=ch)
        return;
    if(judge(x,y) || vis[x][y])
        return;
    num++;
    vis[x][y] = 1;
    if(num >= 16){
        flag=1;
        return ;
    }
    for(int i=0; i<4; i++){
        int ax = x+dir[i][0];
        int ay = y+dir[i][1];
        if(!judge(ax,ay)&&!vis[ax][ay]){
            if(s[ax][ay]==ch){
                num++;
                vis[ax][ay]=1;
                if(num==16){
                    flag=1;
                    return ;
                }
                for(int ii=0; ii<4; ii++)
                    for(int jj=0; jj<4; jj++)
                        if(s[ii][jj]!='W'&&!vis[ii][jj]&&s[ii][jj]!=ch){
                            int a=ii;
                            int b=jj;
                            char c=s[ii][jj];
                            DFS(a, b, c);
                        }
                num--;
                vis[ax][ay]=0;
            }
            else{
                if(s[ax][ay]!='W')
                    continue;
                else
                    DFS(ax,ay,ch);
            }
        }
    }
    num--;
    vis[x][y]=0;
}
int main(){
    for(int i=0; i<4; i++){
        scanf("%s",s[i]);
        getchar();
    }
    int x,y,f=0;
    char ch;
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++)
            if(s[i][j]!='W'){
                x=i;
                y=j;
                ch=s[i][j];
                f=1;
                break;
            }
        if(f==1)
            break;
    }
    memset(vis,0,sizeof(vis));
    num=flag=0;
    DFS(x,y,ch);
    if(flag)
        printf("solvable\n");
    else
        printf("not solvable\n");
    return 0;
}
