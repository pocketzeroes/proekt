#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
enum{ N=200010};
#define inf 1LL<<60
int n,m,i,e[N][4],cnt;

typedef struct{
    int x,y;
}pt;
pt newpt(int x, int y){
    return(pt){x,y};
}
pt w[N<<1];
ll dp[N];
ll ans=inf;
typedef struct Line{
    ll k,b;
}Line;
Line newLine(ll k, ll b){
    return(Line){k,b};
}
ll f(Line l, ll x){
    return l.k * x + l.b;
}
Line*g[N];
int head[N],tail[N],deg[N];

int cmpPt(const void*pa, const void*pb){
    pt*a=(pt*)pa;
    pt*b=(pt*)pb;
    if(a->x!=b->x)
        return(a->x<b->x)?-1:1;
    return(a->y<b->y)?-1:1;
}
inline double pos(Line a, Line b){
    return 1.0*(a.b-b.b)/(b.k-a.k);
}
inline void ins(int o, ll k, ll b){
    if(b>=inf)
        return;
    Line now=newLine(k,b);
#define h head[o]
#define t tail[o]
    if(h<=t){
        if(g[o][t].k==k){
            if(g[o][t].b<=b)
                return;
            t--;
        }
    }
    while(h<t&&pos(g[o][t-1],g[o][t])>=pos(g[o][t],now))
        t--;
    g[o][++t]=now;
}
inline ll cal(int o,ll x){
    if(h>t)
        return inf;
    while(h<t&& f(g[o][h], x) > f(g[o][h+1], x))
        h++;
    return f(g[o][h], x);
    #undef h
    #undef t
}
int main(){
    scanf("%d%d",&n,&m);
    for(i=1;i<=m;i++){
        scanf("%d%d%d%d",&e[i][0],&e[i][1],&e[i][2],&e[i][3]);
        deg[e[i][1]]++;
        w[++cnt]=newpt(e[i][2],-i);
        w[++cnt]=newpt(e[i][3], i);
    }
    qsort(w+1, cnt, sizeof(pt), cmpPt);
    deg[1]++;
    for(i=1;i<=n;i++){
        tail[i]=-1;
        g[i] = calloc(deg[i]+2, sizeof(Line));
    }
    ins(1,0,0);
    for(i=1;i<=cnt;i++){
        int x=w[i].y;
        if(x<0){
            int y=-x;
            dp[y]=cal(e[y][0],e[y][2]);
            if(dp[y]<inf)
                dp[y]+=1LL*e[y][2]*e[y][2];
        }
        else{
            ins(e[x][1],-2LL*e[x][3],dp[x]+1LL*e[x][3]*e[x][3]);
        }
    }
    for(i=1;i<=m;i++)
        if(e[i][1]==n)
            ans = fmin(ans, dp[i]);
    printf("%lld", ans);
    return 0;
}
