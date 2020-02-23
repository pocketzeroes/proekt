int cmp(const void*pa, const void*pb){
    int*aa=(int*)pa;
    int*bb=(int*)pb;
    int a=*aa;
    int b=*bb;
    if(__builtin_popcount(a)!=__builtin_popcount(b))
        return(__builtin_popcount(a)<__builtin_popcount(b))?-1:1;
    return(a<b)?-1:1;
}
int*sortByBits(int*arr, int arrSz, int*rsz){
    qsort(arr, arrSz, sizeof(int), cmp);
   *rsz=arrSz;
    return arr;
}
