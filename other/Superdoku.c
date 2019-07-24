#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
#define mem(a,b) memset(a, b, sizeof(a))
enum{ maxn=105};
int nmap[maxn][maxn],visc[maxn][maxn],visr[maxn][maxn],pos[maxn][maxn],vis[105];
int n,k;

int dfs(int x,int y){
    for(int i=1;i<=n;i++){
        if(!visc[y][i]&&!vis[i]){
            vis[i]=1;
            if(!visr[x][i]||dfs(x,pos[x][i])){
                nmap[x][y]=i;
                pos[x][i]=y;
                visr[x][i]=1;
                return 1;
            }
        }
    }
    return 0;
}
int main(){
    scanf("%d%d",&n,&k);
    for(int i=1;i<=k;i++){
        for(int j=1;j<=n;j++){
            scanf("%d",&nmap[i][j]);
            if(visr[i][nmap[i][j]]||visc[j][nmap[i][j]])
                goto f;
            visr[i][nmap[i][j]]=1;
            visc[j][nmap[i][j]]=1;
        }
    }
    for(int i=k+1;i<=n;i++){
        for(int j=1;j<=n;j++){
            mem(vis,0);
            dfs(i,j);
        }
        for(int j=1;j<=n;j++)
            visc[j][nmap[i][j]] = 1;
    }
    puts("yes");
    for(int i=1;i<=n;i++){
        for(int j=1;j<n;j++)
            printf("%d ",nmap[i][j]);
        printf("%d\n",nmap[i][n]);
    }
    return 0;
 f:;
    puts("no");
    return 0;
}
