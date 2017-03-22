int removeDuplicates(int* nums, int numsSize) {
    int last = -1;
    for (int i=0;i<numsSize;i++)
    {    
        num=nums[i];
        if (last == -1 || nums[last] != num) 
            nums[++last] = num;
    }
    return last + 1;
}
