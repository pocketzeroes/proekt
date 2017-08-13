int y;

int icmp(const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}
int cmp(const void*pa, const void*pb){
    int*ptra=(int*)pa;
    int*ptrb=(int*)pb;
    int a = *ptra;
    int b = *ptrb;
    if(abs(a - y) != abs(b - y))
        return(abs(a - y) < abs(b - y))?-1:1;
    return(a < b)?-1:1;
}
int*findClosestElements(int*arr, int arrSz, int k, int x, int*rsz){
    y = x;
    qsort(arr, arrSz, sizeof(int), cmp);
    int*res = calloc(k, sizeof(int));
    for(int i = 0; i < k; i++)
        res[i] = arr[i];
    qsort(res, k, sizeof(int), icmp);
   *rsz = k;
    return res;
}
