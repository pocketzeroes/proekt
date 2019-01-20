int dp[1<<20][20];

int uniquePathsIII(int**grid, int gridSz, int*grid0sz){
    int H = gridSz;
    int W = grid0sz[0];
    int y,x;
    int sx,sy,gx,gy;
    int sm=0;
    for(y=0;y<H;y++){
        for(x=0;x<W;x++) {
            if(grid[y][x]==1)
                sx=x,sy=y,sm|=1<<(y*W+x);
            if(grid[y][x]==2)
                gx=x,gy=y;
            if(grid[y][x]==-1)
                sm|=1<<(y*W+x);
        }
    }
    memset(dp,0,sizeof(dp));
    dp[sm][sy*W+sx]=1;
    int mask;
    for(mask=0; mask<(1<<(H*W));mask++){
        int cx,cy,i;
        for(cy=0;cy<(H);cy++){
            for(cx=0;cx<(W);cx++){
                if(dp[mask][cy*W+cx]){
                    int d[4]={0,1,-1,0};
                    for(i=0;i<(4);i++){
                        int ty=cy+d[i];
                        int tx=cx+d[i^1];
                        if(ty<0||ty>=H||tx<0||tx>=W)
                            continue;
                        if(mask&(1<<(ty*W+tx)))
                            continue;
                        dp[mask|(1<<(ty*W+tx))][ty*W+tx]+=dp[mask][cy*W+cx];
                    }
                }
            }
        }
    }
    return dp[(1<<(H*W))-1][gy*W+gx];
}
