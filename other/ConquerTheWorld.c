#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define swap(a,b) do{ __typeof(a) tp; tp = a; a = b; b = tp; }while(0)

#define gt getchar()
typedef long long ll;
typedef struct{
  ll  first;
  int second;
}pair;
pair newpair(ll a, int b){
  return(pair){a,b};
}
int cmpP(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}
typedef pair P;
#define mk newpair
#define fr first
#define sc second

static inline int in(){
    int k=0;
    char ch=gt;
    bool p=1;
    while(ch<'-')
        ch=gt;
    if(ch=='-')
        ch=gt,p=0;
    while(ch>'-')
        k=k*10+ch-'0',ch=gt;
    return p?k:-k;
}
enum{N=(int)2.5e5+5};
enum{M=N*30};
int lc[M],rc[M],len[M],tot;
P a[M];
int rtm[N],rth[N],hol[N],mou[N];ll ans,dis[N];
int head[N],to[N<<1],nxt[N<<1],w[N<<1],cnt;

static inline int New(ll x, int y){
    return a[++tot]=mk(x,y),tot;
}
static inline void add(int u, int v, int c){
    to[++cnt]=v,nxt[cnt]=head[u],w[head[u]=cnt]=c;
}
int merge(int x, int y){
    if(!x||!y)
        return x|y;
    if(cmpP(&a[x], &a[y])<0)
        swap(x,y);
    rc[y] = merge(x, rc[y]);
    if(len[lc[y]] < len[rc[y]])
        swap(lc[y], rc[y]);
    len[y] = len[lc[y]]+1;
    return y;
}
void Union(int*x, int*y, ll w){
    while(*x && *y){
        ll vx=a[*x].fr,vy=a[*y].fr,val=vx+vy-w;
        int d = fmin(a[*x].sc, a[*y].sc);
        if(val>=0)
            return;
        ans+=val*d;
        if(!(a[*x].sc-=d))
            *x=merge(lc[*x], rc[*x]);
        if(!(a[*y].sc-=d))
            *y=merge(lc[*y], rc[*y]);
        *x=merge(*x, New(vx-val,d));
        *y=merge(*y, New(vy-val,d));
    }
}
void dfs(int u, int pa){
    for(int i=head[u],v; i; i=nxt[i])
        if((v=to[i])!=pa){
            dis[v]=dis[u]+w[i],dfs(v,u);
            Union(&rtm[u], &rth[v], dis[u]*2);
            Union(&rth[u], &rtm[v], dis[u]*2);
            rtm[u]=merge(rtm[u],rtm[v]);
            rth[u]=merge(rth[u],rth[v]);
        }
#define x rtm[u]
#define y rth[u]
    while(mou[u]){
        ll val=1e14;
        int d=mou[u];
        if(y){
            val=a[y].fr-dis[u];
            d = fmin(d, a[y].sc);
            if(!(a[y].sc-=d))
                y=merge(lc[y],rc[y]);
        }
        ans+=val*d,mou[u]-=d;
        x=merge(x,New(dis[u]-val,d));
    }
    while(hol[u]&&x){
        ll val=a[x].fr-dis[u];
        if(val>=0)
            break;
        int d = fmin(hol[u], a[x].sc);
        ans+=val*d,hol[u]-=d;
        y = merge(y,New(dis[u]-val,d));
        if(!(a[x].sc-=d))
            x=merge(lc[x],rc[x]);
    }
    if(hol[u])
        y=merge(y,New(dis[u],hol[u]));
  #undef x
  #undef y
}
int main(){
    int n=in();
    for(int i=2,u,v,c;i<=n;++i)
        u=in(), v=in(), c=in(), add(u,v,c), add(v,u,c);
    for(int i=1;i<=n;++i){
        hol[i]=in(), mou[i]=in();
        int d = fmin(hol[i], mou[i]);
        hol[i]-=d, mou[i]-=d;
    }
    dfs(1,0);
    printf("%lld\n", ans);
    return 0;
}
