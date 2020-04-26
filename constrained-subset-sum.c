int f[100055],qs[100055];

int constrainedSubsetSum(int*g, int gSz, int k){
    int n=gSz,ans=(int)-2e9,h=0,t=0;
    for(int i=0;i<n;++i){
        while(h!=t&&qs[h]<i-k)
            ++h;
        int w=(h==t)?0:f[qs[h]];
        w=fmax(w,0);
        w+=g[i];
        f[i]=w;
        while(h!=t&&f[qs[t-1]]<f[i])
            --t;
        qs[t++]=i;
        ans = fmax(ans, w);
    }
    return ans;
}
