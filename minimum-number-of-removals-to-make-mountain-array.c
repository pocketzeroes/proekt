#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)

int minimumMountainRemovals(int*nums, int numsSz){
    int n = numsSz;
    int pre[n]; clr(pre);
    int suf[n]; clr(suf);
    for(int i=0; i<n; i++){
        for(int j=0; j<i; j++)
          if(nums[i] > nums[j])
            pre[i] = fmax(pre[j], pre[i]);
        pre[i]++;
    }
    for(int i=n-1; i>=0; i--){
        for(int j=n-1; j>i; j--)
          if(nums[i] > nums[j])
            suf[i] = fmax(suf[j], suf[i]);
        suf[i]++;
    }
    int res = 0;
    for(int i=0; i<n; i++)
      if(pre[i] >= 2 && suf[i] >= 2)
        res = fmax(res, pre[i] + suf[i] - 1);
    return n - res;
}
