int cmp(const void * a, const void * b){
   return( *(int*)a - *(int*)b );
}
int*getStrongest(int*arr, int arrSz, int k, int*rsz){
    qsort(arr, arrSz, sizeof(int), cmp);
    int i = 0, j = arrSz - 1, p = 0;
    int median = arr[(arrSz - 1) / 2];
    int*res = calloc(k, sizeof(int));
    while(p < k)
        if(abs(arr[i] - median) > abs(arr[j] - median))
            res[p++] = arr[i++];
        else
            res[p++] = arr[j--];
    *rsz=k;
    return res;
}
