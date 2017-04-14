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
void reverse(int*nums,int start,int end){
    while( start < end) {
        swap(nums, start, end);
        start++;
        end  --;
    }
}
int cmp (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}

int nextGreaterElement(int n) {
    int*nums=NULL;int numsSz=0;
    for (int x=n; x; x/=10){
        nums=pushback(nums, &numsSz, x%10);
    }
    reverse(nums,0, numsSz-1);
    for (int i=numsSz-2; i>=0; i--){
        if (nums[i]<nums[i+1]){
            int minIndex = i+1;
            for (int j=i+1; j<numsSz; j++){
                if (nums[j]>nums[i] && nums[j]<nums[minIndex])
                    minIndex = j;
            }
            swap(nums, i, minIndex);
            qsort(nums+i+1, numsSz-i-1, sizeof(int), cmp);
            long long result = 0;
            for (int x=0; x<numsSz; x++)
                result = result * 10 + nums[x];
            if (result <= INT_MAX)
                return result;
            else 
                return -1;
        }
    }
    return -1;
}
