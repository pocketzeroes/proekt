#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int cmp(const void * a, const void * b){ return ( *(int*)a - *(int*)b );}

enum{N = 10010};
int n,m,k,S,T,i,j,cnt,q[N],K;
int g[N],ed,v[N],vc[N],vd[N],nxt[N],vis[N],ans;

inline void add(int x, int y, int c, int d){
    v[++ed] = y;
    vc[ed]  = c;
    vd[ed]  = d;
    nxt[ed] = g[x];
    g[x]    = ed;
}
void dfs(int x){
    if(vis[x])
        return;
    vis[x]=1;
    for(int i=g[x];i;i=nxt[i])
        if(vc[i]<=K&&K<=vd[i])
            dfs(v[i]);
}
int main(){
    scanf("%d%d%d%d%d",&n,&m,&k,&S,&T);
    for(i=1;i<=m;i++){
        int a,b,c,d;
        scanf("%d%d%d%d",&a,&b,&c,&d);
        add(a,b,c,d);
        q[++cnt]=c-1;
        q[++cnt]=d;
    }
    qsort(q+1, cnt, sizeof(int), cmp);
    for(i=2;i<=cnt;i++)
        if(q[i]!=q[i-1]){
            K=q[i];
            for(j=1;j<=n;j++)
                vis[j]=0;
            dfs(S);
            if(vis[T])
                ans+=q[i]-q[i-1];
        }
    printf("%d",ans);
    return 0;
}
