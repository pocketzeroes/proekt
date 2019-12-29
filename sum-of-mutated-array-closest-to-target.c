int cmp(const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}
int findBestValue(int*x, int xSz, int t){
    int*xx=calloc(xSz+1, sizeof(int));
    for(int i=0;i<xSz;i++)
        xx[i]=x[i];
    qsort(xx, xSz, sizeof(int), cmp);
    int n = xSz;
    xx[n] = INT_MAX;
    int at = 0, best = INT_MAX, bi, sum = 0;
    for(int i=0; i<=t+5; i++){
        while(xx[at] <= i){
            sum += xx[at];
            at++;
        }
        int tmp = sum + (n - at) * i;
        tmp = abs(tmp - t);
        if(tmp < best){
            best = tmp;
            bi = i;
        }
    }
    return bi;
}
