int*transformArray(int*arr, int arrSz, int*rsz){
    int n = arrSz, i;
    int*a = calloc(n, sizeof(int));
    for(;;){
        for(i=0;i<n;i++)
            if(!i||i==n-1)
                a[i]=arr[i];
        else if(arr[i]>arr[i-1]&&arr[i]>arr[i+1])
            a[i]=arr[i]-1;
        else if(arr[i]<arr[i-1]&&arr[i]<arr[i+1])
            a[i]=arr[i]+1;
        else 
            a[i]=arr[i];
        if(memcmp(a, arr, n*sizeof(int))==0)
            break;
        else
            memcpy(arr, a, n*sizeof(int));
    }
   *rsz=n;
    return a;
}
