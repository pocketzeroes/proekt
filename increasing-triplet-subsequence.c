bool increasingTriplet(int*nums,int numsSize){
    int min = INT_MAX;
    int a   = INT_MAX;
    int b   = INT_MAX;
    for(int i=0;i<numsSize;i++){
        int c=nums[i];
        if (min >= c) 
            min = c;
        else if (b >= c) 
            a = min, b = c;
        else 
            return true;
    }
    return false;
}
