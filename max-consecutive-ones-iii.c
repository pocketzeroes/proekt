int a_length;
bool ok(int h, int*a, int K, int*cum){
    int n = a_length;
    for(int i = 0; i+h <= n; i++){
        if(h-(cum[i+h] - cum[i]) <= K)
            return true;
    }
    return false;
}
int longestOnes(int*a, int aSz, int K){
    int n = aSz;
    a_length = aSz;
    int cum[n+1]; memset(cum, 0, sizeof(cum));
    for(int i=0; i<n; i++)
        cum[i+1] = cum[i] + a[i];
    int low  = -1, 
        high = n+2;
    while(high - low > 1){
        int h = high+low>>1;
        if(ok(h, a, K, cum))
            low = h;
        else
            high = h;
    }
    return low;
}
