#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
typedef long long ll;

int ways(char**s, int pizzaSz, int K){
  int n = pizzaSz;
  int m = strlen(s[0]);
  enum{mod = 1000000007};
  ll dp[K][n][m]; clr(dp);
  for(int i=0; i<n; i++)
    for(int j=0; j<m; j++)
      for(int k=i; k<n; k++)
        for(int l=j; l<m; l++)
          if(s[k][l] == 'A')
            dp[0][i][j] = 1;
  for(int u=1; u<=K-1; u++){
    for(int i=0; i<n; i++){
      for(int j=0; j<m; j++){
        ll t = 0;
        bool has = false;
        for(int k=i+1; k<n; k++){
          if(!has){
            for(int l=j; l<m; l++){
              if(s[k-1][l] == 'A')
                has = true;
            }
          }
          if(has)
            t += dp[u-1][k][j];
        }
        has = false;
        for(int k=j+1; k<m; k++){
          if(!has){
            for(int l=i; l<n; l++){
              if(s[l][k-1] == 'A')
                has = true;
            }
          }
          if(has)
            t += dp[u-1][i][k];
        }
        dp[u][i][j] = t % mod;
      }
    }
  }
  return(int)dp[K-1][0][0];
}
