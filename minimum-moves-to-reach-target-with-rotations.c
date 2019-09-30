int f[105][105][2];

int minimumMoves(int**grid, int gridSz, int*grid0sz){
    int n=gridSz,i,j,ans;
    memset(f,127,sizeof(f));
    f[0][0][0]=0;
    for(i=0;i<n;i++)for(j=0;j<n;j++)if(!grid[i][j]){
        if(i+1<n&&j+1<n&&!grid[i+1][j]&&!grid[i][j+1]&&!grid[i+1][j+1]){
            f[i][j][0]=fmin(f[i][j][0],f[i][j][1]+1);
            f[i][j][1]=fmin(f[i][j][1],f[i][j][0]+1);
            f[i+1][j][0]=fmin(f[i+1][j][0],f[i][j][0]+1);
            f[i][j+1][1]=fmin(f[i][j+1][1],f[i][j][1]+1);
        }
        if(j+2<n&&!grid[i][j+1]&&!grid[i][j+2])f[i][j+1][0]=fmin(f[i][j+1][0],f[i][j][0]+1);
        if(i+2<n&&!grid[i+1][j]&&!grid[i+2][j])f[i+1][j][1]=fmin(f[i+1][j][1],f[i][j][1]+1);
    }
    ans=f[n-1][n-2][0];
    if(ans==2139062143)
        ans=-1;
    return ans;
}
