#define BIT_popcount_L  __builtin_popcount

int GCD_L(int a, int b){
  int r;
  while(b){
    r=a;
    a=b;
    b=r%a;
  }
  return a;
}
int chmax(int*a, int b){
  if(*a<b){
    *a=b;
  }
  return*a;
}
int N;
int score[16][16];
int dp[1000000];

int maxScore(int*A, int Asz){
  int i, mask;
  int m;
  N = Asz;
  for(i=0; i<N; i++){
    int j;
    for(j=0; j<N; j++){
      score[i][j] =GCD_L(A[i], A[j]);
    }
  }
  for(i=0; i<(1<<N); i++){
    dp[i] = -1073709056;
  }
  dp[0] = 0;
  for(mask=0; mask<(1<<N); mask++){
    if(dp[mask] >= 0){
      m =BIT_popcount_L(mask)/ 2 + 1;
      for(i=(0);i<(N);i++){
        if(!((mask) &(1<<(i)))){
          int j;
          for(j=(i+1);j<(N);j++){
            if(!((mask) &(1<<(j)))){
              chmax(&dp[mask|(1<<i)|(1<<j)], dp[mask] + m * score[i][j]);
            }
          }
        }
      }
    }
  }
  return dp[(1<<N)-1];
}
