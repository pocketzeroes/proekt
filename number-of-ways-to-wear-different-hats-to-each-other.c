
#define MD (1000000007U)

int N;
int M = 40;
int A[10][40];
int dp[1024];
int nx[1024];

int numberWays(int**hats, int hatsSz, int*hats0sz){
  int i, k;
  N = hatsSz;
  for(i=0; i<N; i++){
    int j;
    for(j=0; j<M; j++)
      A[i][j] = 0;
  }
  for(i=0; i<N; i++){
    int j;
    for(j=0; j<hats0sz[i]; j++)
      A[i][hats[i][j]-1] = 1;
  }
  for(i=0; i<(1<<N); i++)
    dp[i] = 0;
  dp[0] = 1;
  for(k=0; k<M; k++){
    for(i=0; i<(1<<N); i++){
      nx[i] = dp[i]; nx[i]%=MD;
    }
    for(i=0; i<(1<<N); i++){
      int j;
      for(j=0; j<N; j++){
        if(A[j][k] && !((i) &(1<<(j)))){
          nx[i|(1<<j)] += dp[i];
          nx[i|(1<<j)] %= MD;
        }
      }
    }
    for(i=0; i<(1<<N); i++){
      dp[i] = nx[i];
      dp[i] %= MD;
    }
  }
  return dp[(1<<N)-1]%MD;
}
