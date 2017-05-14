inline int max(int a,int b){return a>b?a:b;}
int minDistance(char*a,char*b){
    enum{N=514};
    int dp[N][N];
    int n=strlen(a),m=strlen(b);
    memset(dp,0,sizeof(dp));
    for ( int i=0; i<n; i++ ) 
      for ( int j=0; j<m; j++ ) {
        if ( a[i]==b[j] ) 
            dp[i+1][j+1]=dp[i][j]+1;
        else 
            dp[i+1][j+1]=max(dp[i][j+1],dp[i+1][j]);
    }
    return n+m-2*dp[n][m];
}
