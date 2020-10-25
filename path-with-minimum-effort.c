int**newmat(int x, int y){
  int**rv = calloc(x, sizeof(int*));
  for(int i=0; i<x; i++)
    rv[i] = calloc(y, sizeof(int));
  return rv;
}
void freemat(int**m, int x){
  for(int i=0; i<x; i++)
    free(m[i]);
  free(m);
  m = NULL;
}
////////////////////////
int**h;
int n,m;
int dx[4]={0,0,-1,1};
int dy[4]={-1,1,0,0};
int mid;
int**vis;

int dis(int x, int y, int a, int b){
    return abs(h[x][y]-h[a][b]);
}
void dfs(int nx, int ny){
    if(vis[nx][ny]) 
        return;
    vis[nx][ny]=1;
    for(int i=0; i<4; i++){
        int x=nx+dx[i],
            y=ny+dy[i];
        if(x<0||n<=x||y<0||m<=y||vis[x][y]||dis(x,y,nx,ny)>mid)
            continue;
        dfs(x,y);
    }
}
bool check(){
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            vis[i][j]=0;
    dfs(0,0);
    return vis[n-1][m-1];
}
int minimumEffortPath(int**heights, int heightsSz, int*heights0sz){
    n=heightsSz;
    m=heights0sz[0];
    h=heights;
    vis=newmat(n,m);
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            vis[i][j]=h[i][j];
    int l=0,r=(int)1e6+5;
    int ans=r;
    while(l<=r){
        mid=(l+r)>>1;
        if(check()){
            ans = fmin(ans, mid);
            r = mid-1;
        }
        else
            l = mid+1;
    }
    freemat(vis,n);
    return ans;
}
