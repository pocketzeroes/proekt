int*smallerNumbersThanCurrent(int*nums, int numsSz, int*rsz){
    int n = numsSz;
    int*ans = calloc(n, sizeof(int));
    for(int i=0; i<n; ++i){
        int cnt=0;
        for(int j=0; j<n; ++j)
            if(nums[i]>nums[j])
                ++cnt;
        ans[i] = cnt;
    }
   *rsz=n;
    return ans;
}
