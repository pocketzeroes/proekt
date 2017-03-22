#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))

int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
void swap(int*nums, int i, int j) {
   int t   = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}
int* findDuplicates(int* nums, int numsSize, int* returnSize) {
    int*result=NULL;
    int i = 0;
    while (i < numsSize) {
        if (nums[i] != nums[nums[i] - 1]) {
            swap(nums,i, nums[i] - 1);
        } 
        else {
            ++i;
        }
    }
    for (i = 0; i < numsSize; ++i) {
        if (i != nums[i] - 1) {
            result=pushback(result,returnSize,nums[i]);
        }
    }
    return result;
}
