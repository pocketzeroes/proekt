int removeDuplicates(int* nums, int numsSize) {
    if (numsSize==0) 
        return 0;
    int k     = 2;
    int left  = 0;
    int right = 1;
    while (right < numsSize) {
        if (nums[left] != nums[right] ||
            (left - k + 1 < 0 || nums[left] != nums[left - k + 1])) {
            ++left;
            nums[left] = nums[right];
        }
        ++right;
    }
    return left + 1; 
}
