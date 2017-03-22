int minPatches(int*nums,int numsSz, int n){
    int patch = 0;
    for (uint64_t miss = 1, i = 0; miss <= n;) {
        if (i < numsSz && nums[i] <= miss)
            miss += nums[i++];
        else {
            miss += miss; 
            ++patch;
        }
    }
    return patch;
}
