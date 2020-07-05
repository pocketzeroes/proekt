int getLastMoment(int n, int*left, int leftSz, int*right, int rightSz){
    int res=0;
    int i;
    for(i=0; i<leftSz ; ++i) res = fmax(res,  left [i]);
    for(i=0; i<rightSz; ++i) res = fmax(res,n-right[i]);
    return res;
}
