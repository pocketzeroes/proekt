int getMax(int*, int);
int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize) {
    if(numsSize == 0) return NULL;
    
    *returnSize = numsSize - k + 1;
    int *result = (int *)malloc(*returnSize * sizeof(int));
    int i; 
    result[0] = getMax(nums, k);
    for(i = 1; i <= numsSize - k; i++) {
        if(nums[i + k - 1] > result[i - 1]) result[i] = nums[i + k - 1];
        else if(nums[i - 1] == result[i - 1]) result[i] = getMax(nums + i, k);
        else result[i] = result[i - 1];
    }
    return result;
}

int getMax(int* nums, int size) {
    int tmp = *nums;
    int i;
    for(i = 1; i < size; i++)
        if(tmp < nums[i]) tmp = nums[i];
    return tmp;
}