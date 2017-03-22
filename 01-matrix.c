
int**updateMatrix(int**matrix,int matrixRowSize,int*matrixColSizes,int**columnSizes,int*returnSize){
    int h=matrixRowSize;
    int w=matrixColSizes[0];
    int**dp=malloc(h*sizeof(int*));
    for( int i=0;i<h;i++){
      dp[i]=malloc(w*sizeof(int));
      for( int j=0;j<w;j++){
        dp[i][j]=INT_MAX;
      }
    }
    int*cols=malloc(h*sizeof(int));
    for( int i=0;i<h;i++)
        cols[i]=w;
    for(int times=0; times<=1; times++){
        for(int i=times?h-1:0; times?i>=0:i<h; times?i--:i++){
            for(int j=times?w-1:0; times?j>=0:j<w; times?j--:j++){
                if(matrix[i][j]==0)
                    dp[i][j]=0;
                else if(dp[i][j]!=0){
                    if(i    &&dp[i-1][j]!=INT_MAX&&dp[i][j]>dp[i-1][j]+1) dp[i][j]=dp[i-1][j]+1;
                    if(j    &&dp[i][j-1]!=INT_MAX&&dp[i][j]>dp[i][j-1]+1) dp[i][j]=dp[i][j-1]+1;
                    if(i<h-1&&dp[i+1][j]!=INT_MAX&&dp[i][j]>dp[i+1][j]+1) dp[i][j]=dp[i+1][j]+1;
                    if(j<w-1&&dp[i][j+1]!=INT_MAX&&dp[i][j]>dp[i][j+1]+1) dp[i][j]=dp[i][j+1]+1;
                }
            }
        }
    }
   *columnSizes=cols;
   *returnSize=h;
    return dp;
}
