typedef long long ll;

int numOfSubarrays(int*arr, int arrSz, int k, int threshold){
    ll now=0;
    for (int i = 0; i < (k); ++i)
        now+=arr[i];
    int an=0;
    if(now>=(ll)threshold*k)
        an++;
    for (int i = (k); i < arrSz; ++i){
        now+=arr[i];
        now-=arr[i-k];
        if(now>=(ll)threshold*k)
            an++;
    }
    return an;
}
