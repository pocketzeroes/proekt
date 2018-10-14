int cmp(const void*a, const void*b){ return ( *(int*)a - *(int*)b ); }
int*sortArrayByParityII(int*a, int aSz, int*rsz){
    int n = aSz;
    for(int i = 0; i < n; i++)
        a[i] = (a[i]&1)<<16|a[i];
    qsort(a, aSz, sizeof(int), cmp);
    int*b = calloc(n, sizeof(int));
    for(int i = 0; i < n/2; i++)
        b[i*2] = a[i]&65535;
    for(int i = 0;i < n/2;i++)
        b[i*2+1] = a[i+n/2]&65535;
   *rsz = n;
    return b;
}
