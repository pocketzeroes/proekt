inline int min(int a,int b){return a<b?a:b;}
inline int max(int a,int b){return a>b?a:b;}

bool PredictTheWinner(int*nums, int numsSz) {
    if (numsSz % 2 == 0 || numsSz == 1) {
        return true;
    }
    int dp[numsSz];
    for (int i = numsSz - 1; i >= 0; --i){
        dp[i] = nums[i];
        for (int j = i + 1; j < numsSz; ++j) {
            dp[j] = max(nums[i] - dp[j], nums[j] - dp[j - 1]);
        }
    }
    return dp[numsSz-1] >= 0;
}
