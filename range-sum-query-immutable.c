typedef struct NumArray {
    int size;
    int *sum;
}NumArray;

struct NumArray* numArrayCreate(int* nums, int numsSize) {
    struct NumArray *array;
    int i;
    array = (struct NumArray*)calloc(1, sizeof(struct NumArray));
    array->sum = (int *) calloc(numsSize+1, sizeof(int));
    array->size = numsSize;
    array->sum[0] = 0;
    for(i = 0; i < numsSize; i++){
        array->sum[i+1] = nums[i] + array->sum[i];
    }
    return array;
}

 int numArraySumRange(struct NumArray* numArray, int i, int j)
{
    int sum = 0;
    if(!numArray)
        return 0;
    sum = numArray->sum[j+1] - numArray->sum[i];
    return sum;
}

void numArrayFree(struct NumArray* numArray) {
    free(numArray->sum);
    free(numArray);
}
