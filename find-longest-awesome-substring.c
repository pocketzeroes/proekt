
int chmax(int*a, int b){
  if(*a<b){
    *a=b;
  }
  return *a;
}

int dp[1024];

int longestAwesome(char*A){
  int i;
  int N = strlen(A);
  int res = -1;
  int mask = 0;
  for(i=(0);i<(N);i++){
    A[i] -= '0';
  }
  for(i=(0);i<(1024);i++){
    dp[i] = 1073709056;
  }
  dp[0] = -1;
  for(i=(0);i<(N);i++){
    int j;
    mask ^= (1<<A[i]);
    chmax(&res, i - dp[mask]);
    for(j=(0);j<(10);j++){
      chmax(&res, i - dp[mask ^ (1<<j)]);
    }
    if(dp[mask] == 1073709056){
      dp[mask] = i;
    }
  }
  return res;
}
