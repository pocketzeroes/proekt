int islandPerimeter(int** grid, int gridRowSize, int gridColSize) {
    int ret = 2;
    int length = gridRowSize * gridColSize;
    int i, j;
    for ( i = 0; i < gridRowSize; i++ ) {
        for ( j = 0; j < gridColSize; j++ ) {
            if ( grid[i][j] ) {
                ret += 4;
                if ( i > 0 && grid[i - 1][j])
                    ret -= 2;
                if ( j > 0 && grid[i][j - 1])
                    ret -= 2;
            }
        }
    }
    return ret-2;
}
