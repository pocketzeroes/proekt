#include <stdlib.h>
#define GetLongestPath(i, j)    (pth[(i) * n + (j)] != 0 ? pth[(i) * n + (j)] : createLongestPths(matrix, pth, m, n, i, j))
#define SetLongestPath(i, j, l) pth[(i) * n + (j)] = l
#define CanMoveToRight()        j < n - 1 && matrix[i][j] < matrix[i][j + 1]
#define CanMoveToDown()         i < m - 1 && matrix[i][j] < matrix[i + 1][j]
#define CanMoveToLeft()         j > 0     && matrix[i][j] < matrix[i][j - 1]
#define CanMoveToUp()           i > 0     && matrix[i][j] < matrix[i - 1][j]
#define RefreshLongest()        if(path > longest) longest = path

int createLongestPths(int** matrix, int* pth, int m, int n, int i, int j){
    int longest = 1, path;
    if(CanMoveToRight()){path = 1 + GetLongestPath(i, j + 1); RefreshLongest();}
    if(CanMoveToDown() ){path = 1 + GetLongestPath(i + 1, j); RefreshLongest();}
    if(CanMoveToLeft() ){path = 1 + GetLongestPath(i, j - 1); RefreshLongest();}
    if(CanMoveToUp()   ){path = 1 + GetLongestPath(i - 1, j); RefreshLongest();}
    SetLongestPath(i, j, longest);
    return longest;
}
int longestIncreasingPath(int** matrix, int m, int n) {
    int* pth = (int *) malloc(m * n * sizeof(int));
    int  longest, path, i;
    if(m * n == 0)
        return 0;
    for(i = 0; i < m * n; ++i)
        pth[i] = 0;
    for(longest = 1, i = 0; i < m * n; ++i)
    {
        if(pth[i] == 0)
        {
            path = createLongestPths(matrix, pth, m, n, i / n, i % n);
            RefreshLongest();
        }
    }
    free(pth);
    return longest;
}

