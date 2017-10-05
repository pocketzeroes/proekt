#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

int N, M, o[1111], lo;
typedef long long ll;
enum{ maxn = 2222      };
enum{ maxm = 66666     };
enum{ inf  = (ll)(1e18)};
int g[maxn],to[maxm],np[maxm],cp;
int n,u,v,now,source,sink;
ll sum,cap[maxm],a[maxn];
int d[maxn],p[maxn],cur[maxn],cnt[maxn];
int q[2222],op,cl;
bool inq[2222];

void add_edge(int x,int y,ll z){
    cap[cp]=z;to[cp]=y;np[cp]=g[x];g[x]=cp++;cap[cp]=0;to[cp]=x;np[cp]=g[y];g[y]=cp++;
}
void init(){
    cp=2; memset(g,0,sizeof(g));
}
ll maxflow(){
    sum=0;
    for(u=1;u<=n;u++)
        cur[u]=g[u]; 
    a[u=source]=inf; 
    memset(d,0,sizeof(int)*(n+1)); 
    memset(cnt,0,sizeof(int)*(n+1)); 
    cnt[0]=n;
    while(d[source]<n){
        for(now=cur[u];now;now=np[now])
            if(cap[now]&&d[v=to[now]]+1==d[u])
                break; 
        cur[u]=now;
        if(now){
            p[v]=now; 
            a[v]=cap[now]; 
            if( a[v]>a[u])
                a[v]=a[u];
            if((u=v)==sink){
                do{
                    cap[p[u]]-=a[sink]; 
                    cap[p[u]^1]+=a[sink]; 
                    u=to[p[u]^1];
                }while(u!=source);
                sum+=a[sink]; 
                a[source]=inf;
            }
        }
        else{
            if(--cnt[d[u]]==0)
                break; 
            d[u]=n; 
            cur[u]=g[u];
            for(now=g[u];now;now=np[now]) 
                if(cap[now] && d[u]>d[to[now]]+1) 
                    d[u]=d[to[now]]+1;
            cnt[d[u]]++;
            if(u!=source)
                u=to[p[u]^1];
        }
    }
    return sum;
}
void bfs(int x){
    q[op++] = x;
    inq[x] = true;
    while(cl<op){
        x=q[cl++];
        for(now=g[x]; now; now=np[now]){
            if(cap[now]){
                int y = to[now];
                if(!inq[y]){
                    inq[y] = true;
                    q[op++] = y;
                }
            }
        }
    }
}
int main(){
    scanf("%d%d",&N,&M);
    init();
    source = N+M+1;
    sink = n = source + 1;
    for(int i=1; i<=N; i++){
        int x;
        scanf("%*d%d",&x);
        add_edge(source, i, x);
    }
    ll res = 0;
    for(int i=1; i<=M; i++){
        int x1,x2,x3,y;
        scanf("%d%d%d%d",&x1,&x2,&x3,&y);
        res += y;
        add_edge(N+i, sink, y);
        add_edge(x1, N+i, inf);
        add_edge(x2, N+i, inf);
        add_edge(x3, N+i, inf);
    }
    printf("%lld", res - maxflow());
    bfs(source);
    for(int i=1; i<=N; i++)
        if(!inq[i])
            o[lo++] = i;
    printf(" %d\n", lo);
    for(int i=0; i<lo; i++)
        printf("%d%c", o[i], (i<lo-1?' ':'\n'));
    return 0;
}






















































