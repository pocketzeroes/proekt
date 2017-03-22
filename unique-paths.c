int uniquePaths(int m, int n) {
    int** pathNums = (int**)malloc(sizeof(int*) * m);
    for (int i = 0; i < m; ++i) 
        pathNums[i] = (int*)malloc(sizeof(int) * n);
    for(int i=0;i<m;i++)
      for(int j=0;j<n;j++)
        pathNums[i][j]=0;
    return helper(pathNums, m - 1, n - 1);
}
int helper(int**pathNums,int m,int n){
    if( m < 0 || n < 0 )
        return 0;
    if( m == 0 || n == 0 )
        return 1;
    if( pathNums[m][n] != 0 )
        return pathNums[m][n];
    pathNums[m][n] = helper(pathNums, m - 1, n) + 
                     helper(pathNums, m, n - 1)  ;
    return pathNums[m][n];
}
