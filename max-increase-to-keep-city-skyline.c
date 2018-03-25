int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

int maxIncreaseKeepingSkyline(int**a, int aSz, int*a0szs){
    int n = aSz, m = a0szs[0];
    int*mr = calloc(n, sizeof(int));
    for(int i = 0;i < n;i++){
        int mx = 0;
        for(int j = 0;j < m;j++){
            mx = max(mx, a[i][j]);
        }
        mr[i] = mx;
    }
    int*mc = calloc(m, sizeof(int));
    for(int i = 0; i < m; i++){
        int mxm = 0;
        for(int j = 0; j < n; j++){
            mxm = max(mxm, a[j][i]);
        }
        mc[i] = mxm;
    }
    int ans = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            ans += min(mr[i], mc[j]) - a[i][j];
        }
    }
	free(mr);
	free(mc);
    return ans;
}
