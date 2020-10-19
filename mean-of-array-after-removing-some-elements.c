int cmp (const void * a, const void * b){ return ( *(int*)a - *(int*)b );}
double trimMean(int*arr, int arrSz){
    double ans = 0;
    qsort(arr, arrSz, sizeof(int), cmp);
    int n = arrSz;
    for(int i = n / 20; i < n / 20 * 19; i++)
        ans += arr[i];
    return ans / (n - (2 * n / 20));
}
