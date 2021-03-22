int dp[105];
int maxAscendingSum(int*a, int aSz){
    int ret=0,n=aSz;
    for(int i=0;i<n;++i){
        int tmp=0,lst=-1;
        for(int j=i;j<n;++j){
            if(a[j]<=lst)
                break;
            lst=a[j];
            tmp+=a[j];
            ret = fmax(ret, tmp);
        }
    }
    return ret;
}
