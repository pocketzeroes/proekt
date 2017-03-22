int* grayCode(int n, int* returnSize){
    int resultSize=(1 << n)+1,i;
    int*result=malloc(resultSize*sizeof(int));
    for(i = 0; i < 1 << n; ++i)
        result[i] = i>>1^i;
    *returnSize=i;
    return result;
}
