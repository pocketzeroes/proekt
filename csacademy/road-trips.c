#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
typedef signed long long ll;
ll min(ll a,ll b){return a<b?a:b;}
ll max(ll a,ll b){return a>b?a:b;}

typedef struct pair{
    int first;
    int second;
}pair;
pair newPair(int a, int b){
    pair rez;
    rez.first =a;
    rez.second=b;
    return rez;
}

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))

pair*pushbackP(pair*array, int *size, pair value){
    pair*output = resizeArray(array, pair, *size + 1);
    output[(*size)++] = value;
    return output;
}
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}




int N,M;
int   V     [101010];
pair* E     [101010];
int   sizes [101010];
int   P [21][101010];
ll    D     [101010];
ll    dist  [101010];
ll    dp    [1<<18 ];
int   LCA   [20][20];
ll    lowest[18][1<<18];
int*L=NULL;int LSz=0;


int lca(int a,int b){
    int tt;
    int ret=0,i,aa=a,bb=b;
    if(D[aa]>D[bb]){
        tt=aa;
        aa=bb;
        bb=tt;
    }
    for(i=19;i>=0;i--) 
        if(D[bb]-D[aa]>=1<<i) 
            bb=P[i][bb];
    for(i=19;i>=0;i--) 
        if(P[i][aa]!=P[i][bb]) 
            aa=P[i][aa], bb=P[i][bb];
    return (aa==bb)?aa:P[0][aa];
}
void dfs(int cur,int pre,ll di,int d) {
    D[cur]=d;
    dist[cur]=di;
    P[0][cur]=pre;
    for(int i=0;i<sizes[cur];i++){
        pair e=E[cur][i];
        if(e.first!=pre) 
            dfs(e.first,cur,di+e.second,d+1);
    }
}
int cmp(const void *a,const void *b)
{
    return *(int *)a-*(int *)b;
}
void solve() {
    int i,j,k,l,r,x,y; 
    scanf("%d %d",&N,&M);
    for(i=0;i<(M);i++) 
        scanf("%d",&V[i]);
    for(i=0;i<(N-1);i++) {
        scanf("%d %d %d",&x,&y,&r);
        x--,y--;
        E[x]=pushbackP(E[x],sizes+x,newPair(y,r));
        E[y]=pushbackP(E[y],sizes+y,newPair(x,r));
    }
    dfs(0,0,0,0);
    for(i=0;i<(19);i++) for(x=0;x<(N);x++) P[i+1][x]=P[i][P[i][x]];
    for(i=0;i<(N);i++) if(i && sizes[i]==1) L=pushback(L,&LSz,i);
    for(y=0;y<(LSz);y++) for(x=0;x<(LSz);x++) LCA[x][y] = lca(L[x],L[y]);
    for(i=0;i<(1<<LSz);i++) {
        for(x=0;x<(LSz);x++) if(i & (1<<x)) {
            for(y=0;y<(LSz);y++) if(x!=y && (i & (1<<y))) lowest[x][i]=max(lowest[x][i],dist[LCA[x][y]]);
        }
    }
    qsort(V,M,sizeof(int),cmp);
    ll ret=0;
    for(x=1;x<=LSz;x++) {
        ll V2[20]={};
        for(i=0;i<(x);i++) {
            if(i==0) V2[i]=V[i];
            else V2[i]=V[i+(M-x)];
        }
        for(int mask=1;mask<1<<LSz;mask++) {
            int id=__builtin_popcount(mask)-1;
            if(id>=x) continue;
            dp[mask]=-1LL<<60;
            for(i=0;i<(LSz);i++) if(mask & (1<<i)) {
                dp[mask]=max(dp[mask], dp[mask ^ (1<<i)] + (dist[L[i]]-lowest[i][mask])*V2[id]);
            }
            ret = max(ret, dp[mask]);
        }
    }
    printf("%lld\n", ret);
}
int main(){
    solve(); 
    return 0;
}






















































