int cmp (const void * a, const void * b){ return ( *(int*)a - *(int*)b );}
int findUnsortedSubarray(int* a, int aSz){
    int*b = malloc(aSz*sizeof(int));
    for(int i=0;i<aSz;i++)b[i]=a[i];
    qsort(b,aSz,sizeof(int),cmp);
    int l = 0, r = aSz;
    while (l < r && a[l  ] == b[l  ]) l++;
    while (l < r && a[r-1] == b[r-1]) r--;
    return r-l;
}
