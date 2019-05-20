#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	int*ptr;
	int sz;
}vec;
vec newVec(){
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
/////////////////
enum{ mod=(int)1e9+7};
enum{Maxn=100020};
int dp1[19][Maxn];
int n,K;
vec G[Maxn];
int f[2][6];
int dp2[19][Maxn];
int pre[Maxn][6],
    suf[Maxn][6];
int ans;

inline void up(int*x, int y){
    (*x)+=y;
    if(*x>=mod)
       *x-=mod;
}
void dfs1(int u, int p){
    for(int i=0; i<G[u].sz; i++){
        int v=G[u].ptr[i];
        if(v==p)
            continue;
        dfs1(v,u);
    }
    dp1[0][u]=1;
    for(int i=1;(1<<i)<=n;i++){
        int cs=0;
        memset(f[cs], 0, sizeof f[cs]);
        f[cs][0]=1;
        for(int j=0;j<G[u].sz;j++){
            int v=G[u].ptr[j];
            if(v==p)
                continue;
            memset(f[cs^1],0,sizeof f[cs^1]);
            for(int k=0;k<=K;k++){
                if(!f[cs][k])
                    continue;
                if(k<K)
                    up(&f[cs^1][k+1],1LL*f[cs][k]*dp1[i-1][v]%mod);
                up(&f[cs^1][k],f[cs][k]);
            }
            cs^=1;
        }
        dp1[i][u]=f[cs][K];
    }
}
void dfs2(int u, int p){
    for(int h=1;(1<<h)<=n;h++){
        memset(pre[0],0,sizeof pre[0]);
        pre[0][0]=1;
        for(int i=0;i<G[u].sz;i++){
            int v=G[u].ptr[i];
            if(v==p){
                memcpy(pre[i+1],pre[i],sizeof pre[i]);
                continue;
            }
            memset(pre[i+1],0,sizeof pre[i+1]);
            for(int j=0;j<=K;j++){
                up(&pre[i+1][j],pre[i][j]);
                if(j<K)
                    up(&pre[i+1][j+1],1LL*dp1[h-1][v]*pre[i][j]%mod);
            }
        }
        int lst=G[u].sz;
        memset(suf[lst], 0, sizeof suf[lst]);
        suf[lst][1]=dp2[h-1][u];
        suf[lst][0]=1;
        for(int i=G[u].sz-1;i>=0;i--){
            int v=G[u].ptr[i];
            if(v==p){
                memcpy(suf[i],suf[i+1],sizeof suf[i+1]);
                continue;
            }
            memset(suf[i],0,sizeof suf[i]);
            for(int j=0;j<=K;j++){
                up(&suf[i][j],suf[i+1][j]);
                if(j<K)
                    up(&suf[i][j+1],1LL*dp1[h-1][v]*suf[i+1][j]%mod);
            }
        }
        for(int i=0;i<G[u].sz;i++){
            int v=G[u].ptr[i];
            if(v==p)
                continue;
            dp2[h][v]=0;
            for(int j=0;j<=K;j++){
                up(&dp2[h][v],1LL*pre[i][j]*suf[i+1][K-j]%mod);
            }
        }
        up(&ans,suf[0][K]);
    }
    for(int i=0;i<G[u].sz;i++){
        int v=G[u].ptr[i];
        if(v==p)
            continue;
        dp2[0][v]=1;
        dfs2(v,u);
    }
}
void solve (){
    for(int i=1;i<=n;i++)
        G[i].sz=0;
    for(int i=1;i<n;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        G[u].ptr = pushback(G[u].ptr, &G[u].sz, v);
        G[v].ptr = pushback(G[v].ptr, &G[v].sz, u);
    }
    ans=n;
    dfs1(1,0);
    dfs2(1,0);
    printf("%d\n",ans);
}
int main () {
    while ( ~scanf ( "%d%d" , &n,&K ) )
        solve ();
    return 0 ;
}
