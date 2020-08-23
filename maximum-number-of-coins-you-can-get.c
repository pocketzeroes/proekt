int cmpr(const void *b, const void *a){
   return ( *(int*)a - *(int*)b );
}
int maxCoins(int*a, int aSz){
    int i=0,j=aSz-1;
    int ans=0;
    qsort(a, aSz, sizeof(int), cmpr);
    while(i<j){
        ++i,--j;
        ans+=a[i];
        ++i;
    }
    return ans;
}
