void fill(int*arr,int sz, int val){
  for(int i=0;i<sz;i++)
    arr[i]=val;
}
int distinctSubsequence(char*a, int mod){
    int n = strlen(a);
    int*bucket = calloc(26, sizeof(int));
    fill(bucket, 26, -1);
    int cum = 0;
    for(int i=0; i<n; i++){
        int v = cum;
        int ind = a[i]-'a';
        if(bucket[ind] == -1)
            v++;
        else
            v += mod - bucket[ind];
        if(v >= mod)
           v -= mod;
        bucket[ind] = cum;
        cum += v;
        if(cum >= mod)
           cum -= mod;
    }
    return cum;
}
int distinctSubseqII(char*S){
    return distinctSubsequence(S, 1000000007);
}
