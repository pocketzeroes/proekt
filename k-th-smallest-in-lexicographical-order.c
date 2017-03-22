#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))

int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}

int findKthNumber(int n, int k) {
    int result = 0;
    int cnts[10]={0};
    for (int i = 1; i <= 9; ++i) 
        cnts[i] = cnts[i - 1] * 10 + 1;
    int*nums=NULL;
    int*numsSz=malloc(sizeof(int));*numsSz=0;
    for (int i = n; i > 0; i /= 10) 
        nums=pushback(nums,numsSz,i % 10);
    int total = n;
    int target = 0;
    for (int i = *numsSz - 1; i >= 0 && k; --i) {
        target = target * 10 + nums[i];
        int start = i == *numsSz - 1 ? 1 : 0;
        for (int j = start; j <= 9; ++j) {
            int candidate = result * 10 + j;
            int num;
            if (candidate < target) 
                num = cnts[i + 1];
            else if (candidate > target) 
                num = cnts[i];
            else
                num = total - cnts[i + 1] * (j - start) - cnts[i] * (9 - j);
            if (k > num) 
                k -= num;
            else {
                result = candidate;
                --k;
                total = num - 1;
                break;
            }
        }
    }
    return result;
}














