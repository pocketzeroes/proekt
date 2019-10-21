double dp[1001];
double nx[1001];

double probabilityOfHeads(double*P, int Psz, int T){
  int i;
  int N = Psz;
  for(i=(0);i<(N+1);i++){
    dp[i] = 0;
  }
  dp[0] = 1;
  for(i=(0);i<(N);i++){
    int k;
    for(k=(0);k<(N+1);k++){
      nx[k] = 0;
    }
    for(k=(0);k<(N);k++){
      nx[k] += dp[k] * (1-P[i]);
      nx[k+1] += dp[k] * P[i];
    }
    for(k=(0);k<(N+1);k++){
      dp[k] = nx[k];
    }
  }
  return dp[T];
}
