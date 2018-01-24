#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

void swap(int*nums, int i, int j) {
   int t   = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}
#define rep(i,n) for(int i=1;i<=n;++i)

char buf[1<<15],*FS,*FT;

inline char mygetc(){
    return (FS==FT&&(FT=(FS=buf)+fread(buf,1,1<<15,stdin),FS==FT))?0:*FS++;
}
inline int read(){
    int x=0,rev=0,ch=mygetc();
    while(ch<'0'||ch>'9'){if(ch=='-')rev=1;ch=mygetc();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+ch-'0';ch=mygetc();}
    return rev?-x:x;
}
enum{ MAXN= 2005};
enum{ MAXM= 1000005};
enum{ D   = 10};
int tot;
typedef struct edge{
    int y,next;
//    static int tot;
}edge;
edge e[MAXM*2+D];
int head[MAXN+D];
inline void connect(int x,int y){
#define k tot
    e[++k].next=head[x]; e[head[x]=k].y=y;
    e[++k].next=head[y]; e[head[y]=k].y=x;
    #undef k
}
int n,m,k=0,cnt;
int mate[MAXN+D];
void init(){
    n=read(),m=n;
    rep(i,n)for(int j=n+1;j<=n*2;++j){
        int x=read();
        if(!x)continue;++k;
        connect(i,j);
        if(!mate[i]&&!mate[j])
            mate[mate[i]=j]=i,cnt++;
    }
}
int lev[MAXN+D],mark[MAXN+D],times;
int que[MAXN+D],fro,rear;
bool bfs(){
    times++;
    memset(lev,0,sizeof lev);
    fro=0,rear=-1;
    for(int i=1;i<=n;i++)
        if(!mate[i])
            lev[que[++rear]=i]=1;
    bool flag=false;
    for(int x;fro<=rear;fro++)
        for(int i=head[x=que[fro]],y;i;i=e[i].next)
            if(!lev[y=e[i].y]){
                lev[y]=lev[x]+1;
                if(mate[y])lev[que[++rear]=mate[y]]=lev[y];
                else flag=true; 
            }
    return flag;
}
bool dfs(int x){
    for(int i=head[x],y;i;i=e[i].next)
        if(mark[y=e[i].y]!=times&&lev[x]<lev[y]){
            mark[y]=times;
            if(!mate[y]||dfs(mate[y]))
            {mate[mate[x]=y]=x;return true;}
        }
    return false;
}
int main(){
    init();
    while(bfs())
        for(int i=1;i<=n;i++)
            if(!mate[i]&&dfs(i))
                cnt++;
    if(cnt!=n)puts("-1");else{
        rep(i,n){
            if(mate[i]-n==i)continue;
            int s=0;
            rep(j,n)if(mate[j]-n==i)s=j;
            printf("R %d %d\n",i,s);
            swap(mate, i, s);
        }
    }
    return 0;
}
