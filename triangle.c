#define MIN(a,b) (((a)<(b))?(a):(b))
int minimumTotal(int** triangle, int triangleRowSize, int *triangleColSizes) {
    int*mini = triangle[triangleRowSize-1];
    for ( int i = triangleRowSize - 2; i>= 0 ; --i )
        for ( int j = 0; j < triangleColSizes[i]; ++ j )
            mini[j] = triangle[i][j] + MIN(mini[j],mini[j+1]);
    return mini[0];
}
