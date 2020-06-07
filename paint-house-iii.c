int f[105][105][25];
int minCost(int*houses, int housesSz, int**cost, int costSz, int*cost0sz, int m, int n, int target){
    int i,j,k,l,ans=1<<30;
    memset(f,127,sizeof(f));
    f[0][0][0]=0;
    for(i=0;i<m;i++)for(j=0;j<=i;j++)for(k=0;k<=n;k++)if(houses[i])f[i+1][j+(k!=houses[i])][houses[i]]=fmin(f[i+1][j+(k!=houses[i])][houses[i]],f[i][j][k]);
    else for(l=1;l<=n;l++)f[i+1][j+(k!=l)][l]=fmin(f[i+1][j+(k!=l)][l],f[i][j][k]+cost[i][l-1]);
    for(l=1;l<=n;l++)ans=fmin(ans,f[m][target][l]);
    if(ans==1<<30)ans=-1;
    return ans;
}
