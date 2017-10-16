int cmpR(const void *b, const void *a){
   return ( *(int*)a - *(int*)b );
}
bool dfs(int*nums, int idx, int*sums, int n, int k, int sum){
    if (n == idx)
        return true;
    for (int i = 0; i < k; i++) {
        if (sums[i] + nums[idx] > sum)
            continue;
        sums[i] += nums[idx];
        if (dfs(nums, idx + 1, sums, n, k, sum))
            return true;
        sums[i] -= nums[idx];
    }
    return false;
}
bool canPartitionKSubsets(int*nums, int numsSz, int k){
    int sum = 0;
    for(int z=0;z<numsSz;z++){ int i = nums[z];
        sum += i;
    }
    if(sum % k != 0)
        return false;
    sum /= k;
    qsort(nums, numsSz, sizeof(int), cmpR);// reverse
    int sums[k]; memset(sums, 0, sizeof(sums));
    return dfs(nums, 0, sums, numsSz, k, sum);
}
