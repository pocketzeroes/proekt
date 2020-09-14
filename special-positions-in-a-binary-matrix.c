int rsum[105];
int csum[105];

int numSpecial(int**mat, int matSz, int*mat0sz){
    int r = matSz;
    int c = mat0sz[0]);
    for(int i = 0; i < r; i++)
        rsum[i] = 0;
    for(int i = 0; i < c; i++)
        csum[i] = 0;
    for(int i = 0; i < r; i++){
      for(int j = 0; j < c; j++){
        rsum[i] += mat[i][j];
        csum[j] += mat[i][j];
      }
    }
    int ret = 0;
    for(int i = 0; i < r; i++)
        for(int j = 0; j < c; j++)
            ret += mat[i][j] == 1 && rsum[i] == 1 && csum[j] == 1;
    return ret;
}
