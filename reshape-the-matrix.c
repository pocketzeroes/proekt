int** matrixReshape(int**a,int asize, int a0size, int r, int c, int**colSz, int* retSz){
   *retSz=asize;
    int*c0ls=malloc(asize*sizeof(int));
    for(int i=0;i<asize;i++)
        c0ls[i]=a0size;
   *colSz=c0ls;
    int**aa=malloc(asize*sizeof(int*));
    for(int i=0;i<asize;i++)
        aa[i]=malloc(a0size*sizeof(int));
    for(int i=0;i<asize;i++)
        for(int j=0;j<a0size;j++)
            aa[i][j]=a[i][j];
    int n = asize;
    if (n == 0)         return aa;
    int m = a0size;
    if (m == 0)         return aa;
    if (n * m != r * c) return aa;
    free(c0ls);
    free(aa);
    int**ret=malloc(r*sizeof(int*));
    for(int i=0;i<r;i++)
        ret[i]=malloc(c*sizeof(int));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int pos = i * m + j;
            ret[pos / c][pos % c] = a[i][j];
        }
    }
    int*cols=malloc(r*sizeof(int));
    for(int i=0;i<r;i++)
        cols[i]=c;
   *colSz=cols;
   *retSz=r;
    return ret;
}

