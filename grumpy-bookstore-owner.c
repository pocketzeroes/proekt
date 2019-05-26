int max(int a,int b){return a>b?a:b;}

int maxSatisfied(int*a, int aSz, int*b, int bSz, int X){
    int n = aSz;
    int ans = 0;
    for(int i=0; i<n; i++)
        if(!b[i] || i<X)
            ans += a[i];
    int cur = ans;
    for(int p=X; p<n; p++){
        int q = p-X;
        if(b[q])
            cur -= a[q];
        if(b[p])
            cur += a[p];
        ans = max(ans, cur);
    }
    return ans;
}
