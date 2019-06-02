#pragma GCC optimize "-O3"
int numSubmatrixSumTarget(int**matrix, int matSz, int*mat0sz, int target){
    int sum[matSz][mat0sz[0]];
    int count = 0;
    for(int i = 0; i < matSz; i++) {
        for (int j = 0; j < mat0sz[0]; j++) {
            sum[i][j] = matrix[i][j] + (i > 0 ? sum[i - 1][j] : 0) + (j > 0 ? sum[i][j - 1] : 0) - (i > 0 && j > 0 ? sum[i - 1][j - 1] : 0);
        }
    }
    for (int i = 0; i < matSz; i++) {
        for (int j = i; j < matSz; j++) {
            for (int k = 0; k < mat0sz[0]; k++) {
                for (int l = k; l < mat0sz[0]; l++) {
                    if (sum[j][l] - (i > 0 ? sum[i - 1][l] : 0) - (k > 0 ? sum[j][k - 1] : 0) + (i > 0 && k > 0 ? sum[i - 1][k - 1] : 0) == target)
                        count++;
                }
            }
        }
    }
    return count;
}
