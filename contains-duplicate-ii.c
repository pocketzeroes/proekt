bool containsNearbyDuplicate(int* nums, int numsSize, int k) {
    int j, i;
    if ( k == 0 )
        return false;
    for ( i = 0 ; i + k < numsSize ; i++ ) {
        j = i + k  ;
        while ( j > i) {
            if (nums[i] == nums[j]) 
                return true;
            j--;
        }
    }
    for ( ; i < numsSize - 1 ; i++) 
        if (nums[i] == nums[numsSize - 1]) 
            return true;
    return false;    
}
