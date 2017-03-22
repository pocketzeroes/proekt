int removeElement(int* nums, int numsSize, int val) {
    int cnt = 0;
    for(int i = 0 ; i < numsSize ; ++i) {
        if(nums[i] == val)
            cnt++;
        else
            nums[i-cnt] = nums[i];
    }
    return numsSize-cnt;
}