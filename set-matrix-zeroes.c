void setZeroes(int** matrix, int matrixRowSize, int matrixColSize) {
    if (matrixRowSize == 0 || matrixColSize == 0)
        return;
    bool has_zero = false;
    int zero_i = -1, zero_j = -1;
    for (int i = 0; i < matrixRowSize; ++i) {
        for (int j = 0; j < matrixColSize; ++j) {
            if (matrix[i][j] == 0) {
                if (!has_zero) {
                    zero_i = i;
                    zero_j = j;
                    has_zero = true;
                }
                matrix[zero_i][j] = 0;
                matrix[i][zero_j] = 0;
            }
        }
    }
    if (has_zero) {
        for (int i = 0; i < matrixRowSize; ++i) {
            if (i == zero_i) 
                continue;
            for (int j = 0; j < matrixColSize; ++j) {
                if (j == zero_j) 
                    continue;
                if (matrix[zero_i][j] == 0 || matrix[i][zero_j] == 0) 
                    matrix[i][j] = 0;
            }
        }
        for (int i = 0; i < matrixRowSize; ++i) 
            matrix[i][zero_j] = 0;
        for (int j = 0; j < matrixColSize; ++j) 
            matrix[zero_i][j] = 0;
    }
}
