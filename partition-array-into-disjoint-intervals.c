int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

int partitionDisjoint(int*a, int aSz){
    int n = aSz;
    int pre[n+1]; memset(pre, 0, sizeof(pre));
    for(int i=0; i<n; i++){
        pre[i+1] = max(pre[i], a[i]);
    }
    int suf[n+1]; memset(suf, 0, sizeof(suf));
    suf[n] = 999999999;
    for(int i = n-1; i >= 0; i--){
        suf[i] = min(suf[i+1], a[i]);
    }
    for(int i = 1; i < n; i++){
        if(pre[i] <= suf[i]){
            return i;
        }
    }
    assert(!"throw new RuntimeException");
}
