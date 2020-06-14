int*runningSum(int*nums, int numsSz, int*rsz){
    int*rv=calloc(numsSz, sizeof(int));
    for(int i=0; i<numsSz; i++){
        rv[i]=nums[i];
    }
    for(int i=1; i<numsSz; i++){
        rv[i] += rv[i-1];
    }
   *rsz=numsSz;
    return rv;
}
