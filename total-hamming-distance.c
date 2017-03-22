int totalHammingDistance(int*nums,int numsSz){
    int size = numsSz;
    if(size < 2) return 0;
    int ans = 0;
    int zero1[2];
    while(true)
    {
        int zeroCount = 0;
        zero1[0] = 0;
        zero1[1] = 0;
        for(int i = 0; i < numsSz; i++)
        {
            if(nums[i] == 0) zeroCount++;
            zero1[nums[i] % 2]++;
            nums[i] = nums[i] >> 1;
        }
        ans += zero1[0] * zero1[1];
        if(zeroCount == numsSz) return ans;
    }
}