char*concatc(char*a, char b){
  char*ptr=NULL;
  asprintf(&ptr, "%s%c",a,b);
  return ptr;
}
void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
char*largestNumber(int*c, int cSz, int m){
    enum{maxd = 9};
    int dp[m + 1]; fill(dp, m+1, INT_MIN);
    dp[0] = 0;
    for(int i = 1; i <= m; ++i)
        for(int j = 0; j < maxd; ++j)
            if(i >= c[j])
                dp[i] = fmax(dp[i], dp[i - c[j]] + 1);
    if(dp[m] < 0)
        return "0";
    char*ret = strdup("");
    while(m>0){
        int pos = -1;
        for(int i=maxd-1; i>=0; --i)
            if(m >= c[i] && (pos == -1 || dp[m - c[i]] > dp[m - c[pos]]))
                pos = i;
        ret = concatc(ret, '1'+pos);
        m -= c[pos];
    }
    return ret;
}
