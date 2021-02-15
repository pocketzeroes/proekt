int minimumSize(int*nums, int numsSz, int maxOperations){
    int lo = 0;
    int hi =(int)1e9 + 7;
    while(lo + 1 < hi){
        int mid = lo + (hi - lo) / 2;
        long long moves = 0;
        for(int z=0;z<numsSz;z++){int x = nums[z];
            moves += (x + mid - 1) / mid;
            --moves;
        }
        if(moves <= maxOperations){
            hi = mid;
        }
        else{
            lo = mid;
        }
    }
    return hi;
}
