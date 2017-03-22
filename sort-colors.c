void swap(int*nums, int i, int j) {
   int t   = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}

void sortColors(int* nums, int numsSize) {
    int target = 1;
    for (int i = 0, j = 0, n = numsSize - 1; j <= n;) {
        if (nums[j] < target) 
            swap(nums,i++,j++);
        else if (nums[j] > target) 
            swap(nums,j,n--);
        else 
            ++j;
    }
}
