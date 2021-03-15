int maximumScore(int*a, int aSz, int k){
    int n = aSz;
    for(int i = k-1;i >= 0;i--){
        a[i] = fmin(a[i], a[i+1]);
    }
    for(int i = k+1;i < n;i++){
        a[i] = fmin(a[i], a[i-1]);
    }
    int ans = 0;
    int l = k, r = k;
    for(int v = a[k];v >= 1;v--){
        while(l-1 >= 0 && a[l-1] >= v)l--;
        while(r+1 < n && a[r+1] >= v)r++;
        ans = fmax(ans, (r-l+1) * v);
    }
    return ans;
}
