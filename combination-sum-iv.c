int compare(const void* x, const void* y) {
    return *(int*)x - *(int*)y;
}

int combinationSum4(int* nums, int numsSize, int target) {
    qsort(nums, numsSize, sizeof(int), compare);

    if (target < nums[0])
	    return 0;

    int* dp = (int*)malloc((target + 1)*sizeof(int)), i, j;
    memset(dp, 0, (target + 1)*sizeof(int));
    dp[0] = dp[nums[0]] = 1;

    for (i = nums[0] + 1; i <= target; i++) {
	    for (j = 0; j < numsSize && i - nums[j] >= 0; j++) {
		    dp[i] +=  dp[i - nums[j]];
	    }
    }

    return dp[target];
}
