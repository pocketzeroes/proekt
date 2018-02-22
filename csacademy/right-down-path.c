#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int max(int a,int b){return a>b?a:b;}
#define MAX(x,y) x=max(x,y)

enum{ N=305};
int n,m,f[N][N][2][2],ma[N][N];

int read(){
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int main(){
    n=read();m=read();
    for (int i=1;i<=n;i++)
        for (int j=1;j<=m;j++)
            ma[i][j]=read();
    int ans=0;
    for (int i=1;i<=n;i++)
        for (int j=1;j<=m;j++){
            if (!ma[i][j]) continue;
            f[i][j][0][0]=1;
            MAX(ans,f[i][j][1][1]);
            MAX(f[i+1][j][1][0],max(f[i][j][0][0],f[i][j][1][0])+1);
            MAX(f[i+1][j][1][1],max(f[i][j][0][1],f[i][j][1][1])+1);
            MAX(f[i][j+1][0][1],max(f[i][j][0][0],f[i][j][0][1])+1);
        }
    printf("%d",ans);
    return 0;
}
