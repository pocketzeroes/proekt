int* singleNumber(int* nums, int numsSize, int* returnSize) {
    int*result=malloc(2*sizeof(int));
    int xor = nums[0];
    for (int i=1; i<numsSize; i++)
    {
        xor ^= nums[i];
    }
    int bit = xor & ~(xor-1);
    int num1 = 0;
    int num2 = 0;
    for (int i=0;i<numsSize;i++){
        int num=nums[i];
        if ((num & bit) > 0)
        {
            num1 ^= num;
        }
        else
        {
            num2 ^= num;
        }
    }
    result[0] = num1;
    result[1] = num2;
    *returnSize=2;
    return result;
}