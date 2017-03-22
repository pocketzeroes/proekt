bool searchMatrix(int** matrix, int matrixRowSize, int matrixColSize, int target) {
    if ( matrixRowSize==0 || matrixColSize==0 )
        return false;
    int m = matrixRowSize;
    int n = matrixColSize;
    int left = 0;
    int right = m * n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (matrix[mid / n][mid % n] >= target) 
            right = mid - 1;
        else 
            left = mid + 1;
    }
    if (left != m * n && matrix[left / n][left % n] == target) 
        return true;
    return false;
}
