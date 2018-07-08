int**transpose(int**a, int aSz, int*a0szs, int**colszs, int*rsz){
    int n = aSz;
    int m = a0szs[0];
    int*cols = calloc(m, sizeof(int));
    int**ret = calloc(m, sizeof(int*));
    for(int i=0; i<m; ++i){
        ret[i] = calloc(n, sizeof(int));
        cols[i]=n;
    }
    for(int i=0; i<n; ++i){
        for(int j=0; j<m; ++j){
            ret[j][i] = a[i][j];
        }
    }
   *colszs=cols;
   *rsz=m;
    return ret;
}
