int wiggleMaxLength(int*nums,int numsSize){
    if (numsSize < 2)
        return numsSize;
    int length = 1, up = 0;
    for (int i = 1; i < numsSize; ++i){
        if (nums[i - 1] < nums[i] && (up == 0 || up == 1))
            ++length, up = -1;
        else if (nums[i - 1] > nums[i] && (up == 0 || up == -1))
            ++length, up = 1;
    }
    return length;
}
