typedef struct {
}SubrectangleQueries;
SubrectangleQueries*gptr;

int A[101][101];
int R, C;

SubrectangleQueries*subrectangleQueriesCreate(int**rectangle, int rectangleSz, int*rectangle0sz){
  R = rectangleSz;
  C = rectangle0sz[0];
  for(int i=0, i_len=(R); i<i_len; ++i) for(int j=0, j_len=(C); j<j_len; ++j) A[i][j] = rectangle[i][j];
  return gptr;
}
void subrectangleQueriesUpdateSubrectangle(SubrectangleQueries* obj, int row1, int col1, int row2, int col2, int newValue) {
  for (int r=row1; r<=row2; r++) for (int c=col1; c<=col2; c++) {
    A[r][c] = newValue;
  }
}
int subrectangleQueriesGetValue(SubrectangleQueries* obj, int row, int col) {
  return A[row][col];
}
void subrectangleQueriesFree(SubrectangleQueries* obj) {
  ;
}
