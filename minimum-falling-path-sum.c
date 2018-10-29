int min(int a,int b){return a<b?a:b;}
void fill(int*arr,int sz, int val){
  for(int i=0;i<sz;i++)
    arr[i]=val;
}
int minFallingPathSum(int**a, int aSz, int*a0sz){
    int m = a0sz[0];
    int*dp = calloc(m, sizeof(int));
    for(int z=0; z<m; z++){
        dp[z] = a[0][z];
    }
    for(int j=0; j<aSz-1; j++){
        int*row = a[j];
        int*ndp = calloc(m, sizeof(int));
        fill(ndp, m, INT_MAX / 2);
        for(int i=0; i<m; i++){
            for(int k=-1; k<=1; k++){
                if(i+k>=0 && i+k < m)
                    ndp[i+k] = min(ndp[i+k], dp[i] + a[j+1][i+k]);
            }
        }
        dp = ndp;
    }
    int ret = INT_MAX;
    for(int z=0;z<m;z++){int v = dp[z];
        ret = min(ret, v);
    }
    return ret;
}
