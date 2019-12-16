int cmp(const void * a, const void * b){ return ( *(int*)a - *(int*)b );}

int findSpecialInteger(int*arr, int arrSz){
    int n = arrSz;
    qsort(arr, arrSz, sizeof(int), cmp);
    for(int i=0; i<n;){
        int j=i;
        while(j<n && arr[j]==arr[i])
            j++;
        if((j-i)*4>n)
            return arr[i];
        i=j;
    }
    return 0;
}
