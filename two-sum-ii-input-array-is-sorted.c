int* twoSum(int* numbers, int numbersSz, int target, int*returnSize) {
    int left = 0, right = numbersSz - 1;
    *returnSize=2;
    while (left != right) {
        int sum = numbers[left] + numbers[right];
        if (sum > target) {
            --right;
        } else if (sum < target) {
            ++left;
        } else {
            int*rez=malloc(2*sizeof(int));
            rez[0]=left  + 1;
            rez[1]=right + 1;
            return rez;
        }
    }
    int*rez=malloc(2*sizeof(int));
    rez[0]=0;
    rez[1]=0;
    return rez;
}
