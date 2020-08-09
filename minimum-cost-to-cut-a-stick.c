int cmp(const void*a, const void*b){ return(*(int*)a-*(int*)b);}

int chmin(int*a, int b){
  if(*a>b){
    *a=b;
  }
  return *a;
}


int N;
int A[200];
int dp[200][200];
int solve(int a, int b){
  int k;
  int tmp;
  int res = 1073709056;
  if(a >= b-1){
    return 0;
  }
  if(dp[a][b] >= 0){
    return dp[a][b];
  }
  for(k=(a+1);k<(b);k++){
    tmp = solve(a,k) + solve(k,b) + A[b] - A[a];
    chmin(&res, tmp);
  }
  return dp[a][b] = res;
}

int minCost(int n, int*cuts, int cutsSz){
  int i;
  qsort(cuts, cutsSz, sizeof(int), cmp);
  N = cutsSz + 2;
  A[0] = 0;
  for(i=(1);i<(N-1);i++){
    A[i] = cuts[i-1];
  }
  A[N-1] = n;
  for(i=(0);i<(N);i++){
    int j;
    for(j=(0);j<(N);j++){
      dp[i][j] = -1;
    }
  }
  return solve(0, N-1);
}
