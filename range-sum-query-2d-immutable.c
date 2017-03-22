typedef struct {
  int a;
}NumMatrix;
int**dp;

NumMatrix*numMatrixCreate(int** matrix, int matrixRowSize, int matrixColSize){
    if (matrixRowSize == 0 || matrixColSize == 0) return NULL;
    dp = malloc(sizeof(int*)*matrixRowSize);
    for (int i=0;i<matrixRowSize;i++)
      dp[i]=malloc(sizeof(int)*(matrixColSize+1));
    for (int r = 0; r < matrixRowSize; r++) 
        for (int c = 0; c < matrixColSize; c++) 
            dp[r][c + 1] = dp[r][c] + matrix[r][c];
    return dp;
}

int numMatrixSumRegion(NumMatrix* obj, int row1, int col1, int row2, int col2){
    int sum = 0;
    for (int row = row1; row <= row2; row++)
        sum += dp[row][col2 + 1] - dp[row][col1];
    return sum;
}

void numMatrixFree(NumMatrix* obj){
    dp=NULL;
}
