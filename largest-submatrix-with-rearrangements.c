int cmpR(const void*b, const void*a){
  return( *(int*)a - *(int*)b );
}
int chmax(int*a, int b){
  if(*a<b)
    *a=b;
  return *a;
}
int dp[100000];
int bg[100000];

int largestSubmatrix(int**A, int Asz, int*A0sz){
  int i, k;
  int X = Asz;
  int Y = A0sz[0];
  int res = 0;
  for(i=0;i<Y;i++){
    dp[i] = 0;
  }
  for(k=(0);k<(X);k++){
    for(i=(0);i<(Y);i++){
      if(A[k][i]){
        dp[i]++;
        continue;
      }
      dp[i] = 0;
    }
    for(i=(0);i<(Y);i++){
      bg[i] = dp[i];
    }
    qsort(bg, Y, sizeof(int), cmpR);//rev
    for(i=(0);i<(Y);i++){
      chmax(&res, bg[i] * (i+1));
    }
  }
  return res;
}
