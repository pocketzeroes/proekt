int subsetSum(int* nums,int numsSz, int S) {
    int dp[S + 1];
    memset(dp,0,sizeof(dp));
    dp[0] = 1;
    for( int i=0;i<numsSz;i++){
        int n=nums[i];
        for (int i = S; i >= n; --i){
            dp[i] += dp[i - n];
        }
    }
    return dp[S];
}
int findTargetSumWays(int* nums, int numsSize, int S) {
    int sum =0;
    for( int i=0;i<numsSize;i++)sum+=nums[i];
    if (sum < S || (S + sum) % 2) 
        return 0;
    return subsetSum(nums,numsSize, (S + sum) / 2); 
}
          