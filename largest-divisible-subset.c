#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}

int cmp(const void *a,const void *b){  return *(int *)a-*(int *)b; }
int*largestDivisibleSubset(int* nums, int numsSize, int* returnSize){
    if (numsSize==0) return NULL;
    qsort(nums,numsSize,sizeof(int),cmp);
    int T     [numsSize];memset(T     , 0,sizeof(T     ));
    int parent[numsSize];memset(parent, 0,sizeof(parent));
    int m  = 0;
    int mi = 0;
    for(int i = numsSize - 1; i >= 0; --i)
    {
        for(int j = i; j < numsSize; ++j)
        {
            if(nums[j] % nums[i] == 0 && T[i] < 1 + T[j])
            {
                T[i] = 1 + T[j];
                parent[i] = j;
                if(T[i] > m)
                {
                    m = T[i];
                    mi = i;
                }
            }
        }
    }
    int*ret=NULL;
    for(int i = 0; i < m; ++i)
    {
        ret=pushback(ret,returnSize,nums[mi]);
        mi = parent[mi];
    }
    return ret;
}


