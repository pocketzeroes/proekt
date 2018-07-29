int min(int a,int b){return a<b?a:b;}
typedef long long ll;
int profitableSchemes(int G, int P, int*group, int groupSz, int*profit, int profitSz){
    int mod = 1000000007;
    int n = groupSz;
    ll dp[G+1][P+1];
    for(int i1=0;i1<G+1;i1++)
      for(int j1=0;j1<P+1;j1++)
        dp[i1][j1]=0;
    
    dp[0][0] = 1;
    for(int i = 0;i < n;i++){
        ll ndp[G+1][P+1];
        for(int i1=0;i1<G+1;i1++)
         for(int j1=0;j1<P+1;j1++)
          ndp[i1][j1]=0;
        for(int j=G; j>=0; j--){
            for(int k=P; k>=0; k--){
                ndp[j][k] += dp[j][k];
                if(ndp[j][k] >= mod)
                   ndp[j][k] -= mod;
                int nk = min(P, k+profit[i]), 
                    nj = j+group[i];
                if(nj <= G){
                    ndp[nj][nk] += dp[j][k];
                    if(ndp[nj][nk] >= mod)
                       ndp[nj][nk] -= mod;
                }
            }
        }
        for(int i1=0;i1<G+1;i1++)
         for(int j1=0;j1<P+1;j1++)
          dp[i1][j1] = ndp[i1][j1];
    }
    ll ret = 0;
    for(int j = 0;j <= G;j++)
        ret += dp[j][P];
    return(int)(ret%mod);
}
