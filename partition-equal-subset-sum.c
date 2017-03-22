int subsetSum(int* nums, int numsSize, int s) {  
    int* dp = (int*)malloc((s + 1) * sizeof(int));  
    for (int i = 0; i <= s; ++i) {  
        dp[i] = 0;  
    }  
    dp[0] = 1;  
    for (int n = 0; n < numsSize; ++n) {  
        for (int i = s; i >= nums[n]; --i) {  
            dp[i] += dp[i - nums[n]];   
        }  
        if (dp[s] > 0) {  
            return dp[s];  
        }  
    }  
    return dp[s];  
}  
bool canPartition(int* nums, int numsSize) {  
    int sum = 0;  
    for (int i = 0; i < numsSize; ++i) {  
        sum += nums[i];  
    }  
    if (sum % 2) {  
        return false;  
    }  
    return subsetSum(nums, numsSize, sum / 2);  
}  
