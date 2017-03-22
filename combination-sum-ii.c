#define newArray(type, size) ((type*)calloc(size, sizeof(type)))
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))

int cmpInt(const void *a, const void *b) {   return *(int*)a - *(int*)b; }

void combinationSum2C(int ***output, int **outputSizes, int *outputSize, int **cache, int *cacheSize, int cacheLen, int target, int *input, int inputSize) {
    if (target == 0) {
        int *result = cacheLen == 0 ? NULL : newArray(int, cacheLen);
        *outputSizes = resizeArray(*outputSizes, int, *outputSize + 1);
        *output = resizeArray(*output, int*, *outputSize + 1);
        if (cacheLen > 0)
        	memcpy(result, *cache, cacheLen * sizeof(int));
        (*output)[*outputSize] = result;
        (*outputSizes)[*outputSize] = cacheLen;
        (*outputSize)++;
    }
    else if (inputSize > 0 && target >= input[0]) {
        int skip = 1;
        if (cacheLen + 1 > *cacheSize) {
            *cacheSize = cacheLen + 4;
            *cache = resizeArray(*cache, int, *cacheSize * sizeof(int));
        }
        (*cache)[cacheLen] = input[0];
        combinationSum2C(output, outputSizes, outputSize, cache, cacheSize, cacheLen + 1, target - input[0], input + 1, inputSize - 1);
        while (skip < inputSize && input[skip] == input[0])
            ++skip;
        if (skip < inputSize)
            combinationSum2C(output, outputSizes, outputSize, cache, cacheSize, cacheLen, target, input + skip, inputSize - skip);
    }
}

int** combinationSum2(int* candidates, int candidatesSize, int target, int** columnSizes, int* returnSize) {
    int **result = NULL, *cache = NULL;
    int cacheSize = *returnSize = 0;
    qsort(candidates, candidatesSize, sizeof(int), cmpInt);
    combinationSum2C(&result, columnSizes, returnSize, &cache, &cacheSize, 0, target, candidates, candidatesSize);
    free(cache);
    return result;
}
