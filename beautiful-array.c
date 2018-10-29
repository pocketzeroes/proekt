int dfs(int d, int m, int n, int*a, int off){
    if(m >= n)
        return off;
    if(m + d >= n){
        a[off++] = m;
        return off;
    }
    for(int i = 0;i < 2;i++){
        off = dfs(d*2, m+d*i, n, a, off);
    }
    return off;
}
int*beautifulArray(int n, int*rsz){
    int*a = calloc(n, sizeof(int));
    dfs(1, 0, n, a, 0);
    for(int i=0; i<n; i++)
        a[i]++;
   *rsz = n;
    return a;
}
