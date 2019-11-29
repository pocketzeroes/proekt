#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;

int read(){
    int x=0,f=1; char ch=getchar();
    while(ch<'0'||ch>'9') { if(ch=='-') f=-1; ch=getchar(); }
    while(ch>='0'&&ch<='9') { x=(x<<1)+(x<<3)+(ch^48); ch=getchar(); }
    return x*f;
}
enum{ N=1007,M =(int)1e5+7};
int n,m,d[M][5],from[M],sav[M],tot;
int mp[N][N];

typedef struct{
    int fa[N];
}dsu;
dsu g[N];

void init(dsu*q){
    for(int i=0; i<=n+2; i++)
        q->fa[i] = i;
}
int find(dsu*q, int x){
    if(x==q->fa[x])
        return x;
    else{
        q->fa[x] = find(q, q->fa[x]);
        return q->fa[x];
    }
}

int main(){
    n=read(),
    m=read(),
    m=read();
    for(int i=0;i<n;i++)
        init(&g[i]);
    int now=0;
    char s[7];
    for(int i=1;i<=m;i++){
        scanf("%s",s+1);
        if(s[1]=='P'){
            for(int j=0;j<5;j++)
                d[i][j]=read();
            from[i]=now;
            now=i;
        }
        else if(s[1]=='S')
            sav[++tot]=now;
        else
            now=sav[read()];
    }
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            mp[i][j]=1;
    int xa,ya,xb,yb,c;
    while(now){
        c  = d[now][0],
        xa = d[now][1],
        ya = d[now][2],
        xb = d[now][3],
        yb = d[now][4];
        for(int i=xa;i<=xb;i+=2)
            for(int j=find(&g[i],ya);j<=yb;j=find(&g[i], j+2))
                g[i].fa[j]=find(&g[i], j+2),mp[i][j]=c;
        for(int i=xa+1;i<=xb;i+=2)
            for(int j=find(&g[i], ya+1);j<=yb;j=find(&g[i], j+2))
                g[i].fa[j] = find(&g[i], j+2), mp[i][j]=c;
        now=from[now];
    }
    for(int i=0;i<n;i++,puts(""))
        for(int j=0;j<n;j++) 
            printf("%d ",mp[i][j]);
    return 0;
}
