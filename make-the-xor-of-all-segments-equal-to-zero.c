int chmin(int*a, int b){
  if(*a>b){
    *a=b;
  }
  return *a;
}
int dp[1024];
int nx[1024];
int cnt[1024];

int minChanges(int*A, int Asz, int K){
  int i, s;
  int N = Asz;
  int tot;
  int mn;
  for(i=(0);i<(1024);i++){
    dp[i] = 1073709056;
  }
  dp[0] = 0;
  for(s=(0);s<(K);s++){
    tot = 0;
    for(i=(0);i<(1024);i++){
      cnt[i] = 0;
    }
    for(i=(s);i<(N);i+=(K)){
      tot++;
      cnt[A[i]]++;
    }
    int WYIGIcGE;
    int t_ynMSdg;
    if(1024==0){
      t_ynMSdg = 0;
    }
    else{
      t_ynMSdg = dp[0];
      for(WYIGIcGE=(1);WYIGIcGE<(1024);WYIGIcGE++){
        t_ynMSdg = fmin(t_ynMSdg, dp[WYIGIcGE]);
      }
    }
    mn =t_ynMSdg;
    for(i=(0);i<(1024);i++){
      nx[i] = mn + tot;
    }
    for(i=(0);i<(1024);i++){
      int j;
      for(j=(s);j<(N);j+=(K)){
        chmin(&nx[i^A[j]], dp[i] + tot - cnt[A[j]]);
      }
    }
    for(i=(0);i<(1024);i++){
      dp[i] = nx[i];
    }
  }
  return dp[0];
}
