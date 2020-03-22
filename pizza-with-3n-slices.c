

int max_L(int a, int b){
  return a>=b?a:b;
}
int chmax(int*a, int b){
  if(*a < b)
     *a = b;
  return a;
}
int N;
int A[1000];
int dp[1000][1000];

int solve(int a, int b){
  int i;
  int res = 0;
  if(a > b){
    return 0;
  }
  if(a >= N){
    {
      int bahur = (N);
      a -= bahur;
      b -= bahur;
    }
  }
  if(dp[a][b] >= 0){
    return dp[a][b];
  }
  for(i=(3);i<(b-a);i+=(3)){
    chmax(&res, solve(a, a+i-1) + solve(a+i, b));
  }
  for(i=(a+1);i<(b);i+=(3)){
    chmax(&res, A[i] + solve(a+1, i-1) + solve(i+1, b-1));
  }
  return dp[a][b] = res;
}
int maxSizeSlices(int*slices, int slicesSz){
  int i;
  int res = -1;
  N = slicesSz;
  for(i=(0);i<(2*N);i++){
    A[i] = slices[i % N];
  }
  for(i=(0);i<(2*N);i++){
    int j;
    for(j=(0);j<(2*N);j++){
      dp[i][j] = -1;
    }
  }
  for(i=(0);i<(N);i++){
    int j;
    for(j=(i+1);j<(2*N);j+=(3)){
      int k;
      for(k=(j+1);k<(2*N);k+=(3)){
        if(k >= i+N){
          break;
        }
        chmax(&res, max_L(max_L(A[i], A[j]), A[k])+ solve(i+1, j-1) + solve(j+1, k-1) + solve(k+1, i-1+N));
      }
    }
  }
  return res;
}
