int cmp(const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}
int largestSumAfterKNegations(int*a, int aSz, int K){
    qsort(a, aSz, sizeof(int), cmp);
    for(int i=0; i<aSz; i++){
        if(a[i] < 0 && K > 0){
            a[i] = -a[i];
            K--;
        }
    }
    qsort(a, aSz, sizeof(int), cmp);
    if(K % 2 == 1){
        a[0] = -a[0];
    }
    int s = 0;
    for(int i=0; i<aSz; i++){int v=a[i];
        s += v;
    }
    return s;
}
