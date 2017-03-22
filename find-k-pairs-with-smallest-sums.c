#define newArray(type, size) ((type*)calloc(size, sizeof(type)))
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int**pushback(int**array, int *size, int*value) {
    int**output = resizeArray(array, int*, *size + 1);
    output[(*size)++] = value;
    return output;
}
inline int min(int a,int b){return a<b?a:b;}
inline int max(int a,int b){return a>b?a:b;}

int** kSmallestPairs(int* nums1, int nums1size, int* nums2, int nums2size, int k, int** columnSizes, int* returnSize) {
    if(nums1size==0||nums2size==0) {
        return NULL;
    }
    int len1 = nums1size, len2 = nums2size, cnt = min(k, len1*len2);
    int index[len1];
    memset(index,0,sizeof(index));
    int**ans=NULL;
    while(cnt-- > 0)
    {
        int temMin = INT_MAX, m = 0;
        for(int i =0; i < len1; i++)
            if(index[i] < len2 && nums1[i]+nums2[index[i]] < temMin)
                temMin= nums1[i]+nums2[index[i]], m = i;
        int*pair=malloc(2*sizeof(int));
        pair[0]=nums1[m];
        pair[1]=nums2[index[m]++];
        ans=pushback(ans, returnSize, pair);
    }
    
    int* columns = (int*)malloc( *returnSize * sizeof(int) );
    for(int i=0; i<*returnSize; i++) columns[i]=2;
    *columnSizes = columns;
    return ans;
}
