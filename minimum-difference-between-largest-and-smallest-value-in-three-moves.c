int cmp(const void*a, const void*b){ return(*(int*)a-*(int*)b);}

int minDifference(int*nums, int numsSz){
    if(numsSz<=4)
        return 0;
    qsort(nums, numsSz, sizeof(int), cmp);
    int ans=(int)2e9;
    for(int i=3, j=numsSz-1; ~i; --i, --j)
        ans = fmin(nums[j]-nums[i], ans);
    return ans;
}
