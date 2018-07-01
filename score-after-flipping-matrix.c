int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}
int matrixScore(int**A, int Asz, int*A0sz){
  int rows = Asz;
  int cols = A0sz[0];
  int res  = 0;
  int mat[rows][cols];
  for(int fst = 0, __fst = 2; fst < __fst; ++fst) {
    int now  = 0;
    for(int i=0;i<rows;i++)
    for(int j=0;j<cols;j++)
      mat[i][j]=A[i][j];
    if(fst)
      for(int r = 0, __r = rows; r < __r; ++r) 
          mat[r][0] ^= 1;
    for(int r = 0, __r = rows; r < __r; ++r) 
      if(mat[r][0] == 0) {
        for(int c = 0, __c = cols; c < __c; ++c) 
          mat[r][c] ^= 1;
      }
    for(int c = 0, __c = cols; c < __c; ++c) {
      int cnt = 0;
      for(int r = 0, __r = rows; r < __r; ++r) 
        cnt += mat[r][c];
      now += max(cnt, rows - cnt) << (cols - c - 1);
    }
    res = max(res, now);
  }
  return res;
}
