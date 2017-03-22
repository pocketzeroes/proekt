void traverse(int* nums, int size, int begin, int k, int* stack, int top, int*** arr, int** colSize, int* returnSize)
{
    if(top+1==k)
    {
        *returnSize += 1;
        *colSize = (int*)realloc(*colSize, sizeof(int)*(*returnSize));
        (*colSize)[*returnSize-1] = k;
        *arr = (int**)realloc(*arr, sizeof(int*)*(*returnSize));
        (*arr)[*returnSize-1] = (int*)malloc(sizeof(int)*k);
        for(int i = 0; i < k; i++)
            (*arr)[*returnSize-1][i] = stack[i];
        return ;
    }
    for(int i = begin; i < size; i++)
    {
        stack[top+1] = nums[i];
        traverse(nums, size, i+1, k, stack, top+1, arr, colSize, returnSize);
    }
}

int** combine(int n, int k, int** colSize, int* returnSize)
{
    int *nums = (int*)malloc(sizeof(int)*n);
    for(int i = 0; i < n; i++)
        nums[i] = i+1;
    int *stack = (int*)malloc(sizeof(int)*k);
    int top = -1;
    *returnSize = 0;
    int **arr = (int**)malloc(sizeof(int*));
    for(int i = 0; i <= n-k; i++)
    {
        stack[top+1] = nums[i];
        traverse(nums, n, i+1, k, stack, top+1, &arr, colSize, returnSize);
    }
    return arr;
}

