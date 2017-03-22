#define MIN(a, b) ((a) < (b) ? (a) : (b))
int* intersection(int* nums1, int size1, int* nums2, int size2, int* returnSize)
{
    int size = MIN(size1, size2);
    int *arr = (int*)malloc(sizeof(int)*(size));
    int top = -1;
    for(int i = 0; i < size1; i++) 
    {
        int j = 0;
        for(; j < size2; j++) 
            if(nums1[i] == nums2[j]) break;
        if(j < size2)
        {
            j = 0;
            for(; j <= top; j++) 
                if(arr[j] == nums1[i]) break;
            if(j > top)
                arr[++top] = nums1[i];
        }
    }
    *returnSize = top+1;
    return arr;
}
