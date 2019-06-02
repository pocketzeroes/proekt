int max(int a,int b){return a>b?a:b;}

int maxEqualRowsAfterFlips(int**matrix, int matrixSz, int*matrix0sz){
    int n = matrixSz,
        m = matrix0sz[0];
    int ret = 1;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++)
            if (matrix[i][j] == 0) 
                for (int k = 0; k < n; k++)
                    matrix[k][j] ^= 1;
        int sum = 0;
        for (int j = 0; j < n; j++){
            int flag = 1;
            for (int k = 1; k < m; k++)
                if (matrix[j][k] != matrix[j][0]){
                    flag = 0;
                    break;
                }
            sum += flag;
        }
        ret = max(ret, sum);
    }
    return ret;
}
