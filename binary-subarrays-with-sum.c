int numSubarraysWithSum(int*a, int aSz, int S){
    int n = aSz;
    int*cum = calloc(n+1, sizeof(int));
    for(int i=0; i<n; i++)
        cum[i+1] = cum[i] + a[i];
    int ret = 0;
    int f[30003]; memset(f, 0, sizeof(f));
    for(int i=0; i<=n; i++){
        if(cum[i]-S >= 0)
           ret += f[cum[i]-S];
        f[cum[i]]++;
    }
    return ret;
}
