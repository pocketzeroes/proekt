int* findDisappearedNumbers(int* nums, int numsSize, int* returnSize) {
    int i;
    int index;
    int *ret = malloc(sizeof(int) * numsSize);
    
    for ( i = 0; i < numsSize; i++ ) {
        index = abs(nums[i]) - 1;
        nums[index] = nums[index] > 0 ? nums[index] * (-1) : nums[index];
    }
    
    index = 0; 
    for ( i = 0; i < numsSize; i++ ) {
        if ( nums[i] > 0 ) {
            ret[index] = (i + 1);
            index++;
        }
            
    }
    
    *returnSize = index;
    return ret;
}