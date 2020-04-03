#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

#define ls son[x][0]
#define rs son[x][1]
#define rep(i,l,r) for(int i=(l); i<=(r); i++)
typedef long long ll;

enum{N=100010};
int n,m,top,a[N],son[N][2],stk[N];
ll sm[N],f[N],g[N];

int dfs(int x, int fa){
    if(!x)
        return 0;
    int w=dfs(ls,x)+dfs(rs,x)+1;
    sm[x]=a[x]+sm[ls]+sm[rs];
    ll r=1ll*(a[x]-a[fa])*w-(g[ls]+g[rs]);
    f[x]=f[ls]+f[rs]+fmaxl(0ll,(r+m-1)/m);
    g[x]=f[x]*m-(sm[x]-1ll*a[fa]*w);
    return w;
}
int main(){
    scanf("%d %d", &n, &m);
    rep(i,1,n) scanf("%d", &a[i]);
    rep(i,1,n){
        while(top&&a[stk[top]]>a[i])
            son[i][0]=stk[top--];
        son[stk[top]][1]=i; 
        stk[++top]=i;
    }
    dfs(stk[1],0);
    printf("%lld\n", f[stk[1]]);
    return 0;
}
