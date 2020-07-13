int numIdenticalPairs(int*nums, int numsSz){
    int ret = 0;
    for(int i = 0; i < numsSz; i++)
        for(int j = 0; j < i; j++)
            ret += nums[i] == nums[j];
    return ret;
}
