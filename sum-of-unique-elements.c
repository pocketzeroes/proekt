int cmp(const void * a, const void * b){ return ( *(int*)a - *(int*)b );}
int sumOfUnique(int*nums, int numsSz){
    qsort(nums, numsSz, sizeof(int), cmp);
    int ans = 0;
    for(int i=0, i_len=numsSz; i<i_len; ++i){
        bool yes = true;
        if(i && nums[i-1] == nums[i]) yes = false;
        if(i+1 < numsSz && nums[i] == nums[i+1]) yes = false;
        if(yes) ans += nums[i];
    }
    return ans;
}
