#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
#ifdef _WIN32
  #define inline static
#endif


#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}

#define MAXN 100000

int*G [MAXN+1];
int sz[MAXN+1];
bool marked[MAXN+1];
int distA[2][MAXN+1],distB[2][MAXN+1];
int Q[MAXN+1];
bool path[MAXN+1];
int dp[MAXN+1];
inline void add_Edge(int x,int y){
    G[x]=pushback(G[x], sz+x, y);
}
inline void BFS(int s,int d,int *dist){
    int b,e,x,nod;
    memset(marked,0,sizeof(marked));
    b=0;
    e=1;
    Q[0]=s;
    dist[s]=1;
    marked[s]=1;
    do{
        nod=Q[b];
        for(int i=0;i<sz[nod];i++){ int x = G[nod][i];
          if(marked[x]==0){
             marked[x]=1;
             dist[x]=dist[nod]+1;
             Q[e]=x;
             e++;
          }
        }
        b++; 
    }while(b<e);
}
inline int getmax(int a,int b){
    if(a<b) return b;
    return a;
}
inline void solve(int s,int d){
    int b,e,x,nod;
    memset(marked,0,sizeof(marked));
    b=0;
    e=1;
    Q[0]=s;
    marked[s]=1;
    do{
        nod=Q[b];
        for(int i=0;i<sz[nod];i++){ int x = G[nod][i];
         if(marked[x]==0){
             marked[x]=1;
             if(path[x]==1&&path[nod]==1)
               dp[x]=dp[nod]+1;
             Q[e]=x;
             e++;
         }
         else
            if(distA[0][x]==distA[0][nod]+1&&path[x]==1&&path[nod]==1)
              dp[x]=getmax(dp[x],dp[nod]+1);
        }
        b++; 
    }while(b<e);
}
int main() {
    int i,n,m,s,a,b,ans,x,y;
    scanf("%d %d",&n,&m);
    scanf("%d %d %d",&s,&a,&b);
    for(i=1;i<=m;i++){
        scanf("%d %d",&x,&y);
        add_Edge(x,y);
        add_Edge(y,x);
    }
    BFS(s,a,distA[0]);
    BFS(a,s,distA[1]);
    BFS(s,b,distB[0]);
    BFS(b,s,distB[1]);
    ans=0;
    for(i=1;i<=n;i++)
      if(distA[0][i]+distA[1][i]==distA[0][a]+1&&distB[0][i]+distB[1][i]==distB[0][b]+1)
        path[i]=1;
    solve(s,a);
    for(i=1;i<=n;i++)
      if(ans<dp[i])
        ans=dp[i];
    printf("%d\n", ans);
    return 0;
}


