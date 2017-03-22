bool searchMatrix(int** matrix, int m, int n, int target) {
    if (m == 0||n == 0) 
        return false;
    int count = 0;
    int i = 0, j = n - 1;
    while (i < m && j >= 0) {
        if (matrix[i][j] == target)
            return true;
        else if (matrix[i][j] > target)
            --j;
        else
            ++i;
    }
    return false;
}
