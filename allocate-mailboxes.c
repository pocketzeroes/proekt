int cmp (const void*a, const void*b){ return(*(int*)a-*(int*)b);}
void amin(int*x, int y){
    if(y<*x)
       *x=y;
}
int min_element(int*arr, int sz){
  int mine = arr[0];
  for(int i=1;i<sz;i++)
    if(arr[i]<mine)
      mine=arr[i];
  return mine;
}

int dp[111][111];
int sums[111];

int minDistance(int*houses, int housesSz, int k){
    qsort(houses, housesSz, sizeof(int), cmp);
    int N = housesSz;
    for(int i=0, i_len=(N); i<i_len; ++i)
        sums[i+1] = sums[i] + houses[i];
    memset(dp, 0x3f, sizeof dp);
    dp[0][0] = 0;
    for(int i=0, i_len=(N); i<i_len; ++i){
        for (int c=1; i+c<=N; c++){
            int mid = houses[i+c/2];
            int cst = sums[i+c]-sums[i+c/2] - mid * (c-c/2);
            cst += mid * (c/2) - (sums[i+c/2]-sums[i]);
            for(int j=0, j_len=(k); j<j_len; ++j){
                amin(&dp[i+c][j+1], dp[i][j] + cst);
            }
        }
    }
    int ans = min_element(dp[N], k+1);
    return ans;
}
