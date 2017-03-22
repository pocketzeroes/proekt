void traverse(int* nums, int size, int start, int k, int target, int* stack, int top, int*** arr, int** colSizes, int* returnSize)
{
    if(top+1 == k) 
    {
        if(target==0) 
        {
            *returnSize += 1;
            *colSizes = (int*)realloc(*colSizes, sizeof(int)*(*returnSize));
            (*colSizes)[*returnSize-1] = k;
            *arr = (int**)realloc(*arr, sizeof(int*)*(*returnSize));
            (*arr)[*returnSize-1] = (int*)malloc(sizeof(int)*k);
            for(int i = 0; i < k; i++)
                (*arr)[*returnSize-1][i] = stack[i];
        }
        return ;
    }
    for(int i = start; i < size; i++)
    {
        if(nums[i] > target) return ; 
        stack[top+1] = nums[i]; 
        traverse(nums, size, i+1, k, target-nums[i], stack, top+1, arr, colSizes, returnSize);
    }
}
int** combinationSum3(int k, int target, int** colSizes, int* returnSize)
{
    int nums[] = {1,2,3,4,5,6,7,8,9};
    int size = sizeof(nums)/sizeof(int);
    int** arr = (int**)malloc(sizeof(int*));
    *returnSize = 0;
    *colSizes = (int*)malloc(sizeof(int));
    int *stack = (int*)malloc(sizeof(int)*k);
    int top = -1;
    for(int i = 0; i < size; i++)
    {
        if(nums[i] > target) break; 
        stack[top+1] = nums[i];
        traverse(nums, size, i+1, k, target-nums[i], stack, top+1, &arr, colSizes, returnSize);
    }
    return arr;
}
