#define MAX 12

int set[MAX];
int result_size[1<<MAX];
int temp_result[1<<MAX][MAX];
int count;
int **result;

void xmemcpy(int *dst, int *src, int n)
{
    while(n--)
        *dst++ = *src++;
}

void sort(int *a, int n)
{
    int i;
    int j;
    int t;
    for(i=1; i<=n; i++)
    {
        for(j=0; j<n-i; j++)
        {
            if(a[j] > a[j+1])
            {
                t = a[j];
                a[j] = a[j+1];
                a[j+1] = t;
            }
        }
    }
}

void helper(int *a, int start, int index, int N, int K)
{
    int i;
   
    if(K == 0 || start == N)
    {
        xmemcpy(temp_result[count], set, index);
        result_size[count] = index;
        count++;
        return;
    }
    
    set[index] = a[start];
    helper(a, start+1, index+1, N, K-1);
    while(start < N-1 && a[start] == a[start+1])
        start++;
    helper(a, start+1, index, N, K-1);
}

int** subsetsWithDup(int* nums, int numsSize, int** columnSizes, int* returnSize) {
    int i;
    count = 0;
    sort(nums, numsSize);
    helper(nums, 0, 0, numsSize, numsSize);
    *returnSize = count;
    *columnSizes = (int*) malloc(sizeof(int)*count);
    if(*columnSizes == NULL)
        exit(1);
    xmemcpy(*columnSizes, result_size, count);
    result = (int**)malloc(sizeof(int*)*count);
    if(!result)
        exit(1);
    for(i=0; i<count; i++)
    {
        result[i] = (int*) malloc(sizeof(int)*result_size[i]);
        if(!result[i])
            exit(1);
        xmemcpy(result[i], temp_result[i], result_size[i]);
    }
    return result;
}

