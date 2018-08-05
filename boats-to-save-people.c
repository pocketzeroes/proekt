int cmp(const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}
int numRescueBoats(int*a, int aSz, int limit){
    qsort(a, aSz, sizeof(int), cmp);
    int n = aSz;
    int p = 0;
    int ct = 0;
    for(int i = n-1;i >= p;i--){
        if(p < i && a[i] + a[p] <= limit)
            p++;
        ct++;
    }
    return ct;
}
