#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))
int**dist;
int**dp;
int n;
enum{ inf=0x3f3f3f3f};
void fill(int*arr,int sz, int val){
    for(int i=0;i<sz;i++)
        arr[i]=val;
}

int dfs(int now, int st){
    if(st==(1<<n)-1) 
        return 0;
#define d dp[now][st]
    if(d+1) 
        return d;
    d = inf;
    for(int i=0; i<n; i++)
      if((st>>i&1) == 0)
        d = min(d, dfs(i,st|(1<<i))+dist[now][i]);
    return d;
#undef d
}
int shortestPathLength(int**graph, int graphSz, int*graph0sz){
    n = graphSz;
    dist = calloc(n, sizeof(int*));
    for(int i=0; i<n; i++){
        dist[i] = calloc(n, sizeof(int));
        fill(dist[i], n, inf);
    }
    for(int i=0; i<n; i++) 
        dist[i][i] = 0;
    for(int i=0; i<n; i++)
        for(int z=0;z<graph0sz[i];z++){int t=graph[i][z];
            dist[i][t] = dist[t][i] = 1;
        }
    for(int k=0; k<n; k++)
      for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
          dist[i][j] = min(dist[i][j], dist[i][k]+dist[k][j]);
    dp = calloc(n,sizeof(int*));
    for(int i=0; i<n; i++){
        dp[i]=calloc(1<<n, sizeof(int));
        fill(dp[i], 1<<n, -1);
    }
    int ans=inf;
    for(int i=0; i<n; i++)
      ans = min(ans,dfs(i,1<<i));
    return ans;
}
