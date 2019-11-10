int**newmat(int x, int y){
  int**rv = calloc(x, sizeof(int*));
  for(int i=0; i<x; i++)
    rv[i] = calloc(y, sizeof(int));
  return rv;
}

int**reconstructMatrix(int upper, int lower, int*colsum, int colsumSz, int*rsz, int**csz){
    int n = colsumSz;
    int**answer = newmat(2, n);
    for (int i = 0; i < n; i++){
        if (colsum[i] == 2) {
            answer[0][i] = answer[1][i] = 1;
            upper--;
            lower--;
        }
    }
    int count_ones = 0;
    for(int i = 0; i < n; i++)
        count_ones += colsum[i] == 1;
    if(upper < 0 || lower < 0 || count_ones != upper + lower){
        int*cols=calloc(1,sizeof(int));
       *csz=cols;
       *rsz = 0;
        return newmat(1,1);
    }
    for (int i = 0; i < n; i++){
        if (colsum[i] == 1) {
            if (upper > 0) {
                answer[0][i] = 1;
                upper--;
            }
            else
                answer[1][i] = 1;
        }
    }
    int*cols = calloc(2, sizeof(int));
    cols[0] = cols[1] = n;
   *csz = cols;
   *rsz = 2;
    return answer;
}
