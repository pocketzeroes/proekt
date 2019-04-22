int dist(int*a, int r0, int c0){
    return abs(a[0]-r0) + abs(a[1] - c0);
}

int**allCellsDistOrder(int R, int C, int r0, int c0, int** columnSizes, int*returnSize){
    int rc=R*C;
    int**rez=calloc(rc, sizeof(int*));
    for(int i=0;i<rc;i++)
        rez[i]=calloc(2,sizeof(int));
    ////
    for(int i = 0; i < R; i++){
        for(int j = 0; j < C; j++){
            rez[i*C + j][0] =i;
            rez[i*C + j][1] =j;
        }
    }
int cmp(const void*pa, const void*pb){
    int**aa=(int**)pa;
    int**bb=(int**)pb;
    int*a = *aa;
    int*b = *bb;
    return(dist(a, r0, c0) - dist(b, r0, c0));
    
}
    qsort(rez,rc,sizeof(int*), cmp);
/////    
    int*cols=calloc(rc, sizeof(int));
    for(int i=0;i<rc;i++)
        cols[i]=2;
   *columnSizes=cols;
   *returnSize = rc;
    return rez;
}

