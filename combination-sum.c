static int cmpint(const void *p1, const void *p2) {
    const int *x = (const int *)p1;
    const int *y = (const int *)p2;
    return *x - *y;
}

#define newObject(type) ((type*)calloc(1, sizeof(type)))
#define newArray(type, size) ((type*)calloc(size, sizeof(type)))
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))

void combinationSumC(
    int target, int *ins, int inSize,
    int *cache, int cacheSize,
    int ***outs, int *outSize, int **outSizes)
{
    if (target == 0) {
        *outs = resizeArray(*outs, int*, *outSize + 1);
        *outSizes = resizeArray(*outSizes, int, *outSize + 1);
        (*outs)[*outSize] = newArray(int, cacheSize);
        memcpy((*outs)[*outSize], cache, cacheSize * sizeof(int));
        (*outSizes)[*outSize] = cacheSize;
        ++*outSize;
    } else if (inSize > 0) {
        int *inEnd = ins + inSize;
        int *tryNum = ins, *tryNext;
        while (1) {
            if (*tryNum > target)
                break;
            cache[cacheSize] = *tryNum;
            combinationSumC(target - *tryNum, tryNum, inEnd - tryNum, cache, cacheSize + 1, outs, outSize, outSizes);
            cacheSize;
            for (tryNext = tryNum; tryNext < inEnd; ++tryNext)
                if (*tryNext != *tryNum)
                    break;
            if (tryNext >= inEnd)
                break;
            tryNum = tryNext;
        }
    }
}

int** combinationSum(int* candidates, int candidatesSize, int target, int** columnSizes, int* returnSize) {
    int *cache = newArray(int, target);
    int **results = *columnSizes = NULL;
    *returnSize = 0;
    qsort(candidates, candidatesSize, sizeof(*candidates), cmpint);
    combinationSumC(target, candidates, candidatesSize, cache, 0, &results, returnSize, columnSizes);
    free(cache);
    return results;
}
