bool kLengthApart(int*nums, int numsSz, int k){
    int last = -(k + k + 1000000);
    for(int i=0; i<numsSz; i++){
        if(nums[i]){
            if(i - last - 1 < k)
                return false;
            last = i;
        }
    }
    return true;
}
