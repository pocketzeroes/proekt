#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define pacific (0x1)
#define atlantic (0x2)
#define both(x) ((x&0x3)==0x3)
#define land (0x4)
#define counted (0x8)
#define left (1)
#define right (2)
#define up (3)
#define down (4)


unsigned char fromfrom(int **matrix, int matrixRowSize, int matrixColSize, unsigned char **map, int x, int y, int from, int *returnSize)
{
    if (!(map[x][y]&0x3))
    {
        return 0;
    }
    if(x>0)
    {
        if (matrix[x][y] <= matrix[x - 1][y] && (map[x][y]|map[x-1][y])>map[x-1][y] )
        { 
            map[x-1][y] |= map[x][y];
            fromfrom(matrix, matrixRowSize, matrixColSize, map, x-1, y, down, returnSize);
        }
    }
    if(x+1 < matrixRowSize)
    {
        if (matrix[x][y] <= matrix[x + 1][y] && (map[x][y]|map[x+1][y])>map[x+1][y] )
        {
            map[x+1][y] |= map[x][y];
            fromfrom(matrix, matrixRowSize, matrixColSize, map, x+1, y, down, returnSize);
        }
    }
    
    if(y>0)
    {
        if (matrix[x][y] <= matrix[x][y-1] && (map[x][y]|map[x][y-1])>map[x][y-1] )
        {
            map[x][y-1] |= map[x][y];
            fromfrom(matrix, matrixRowSize, matrixColSize, map, x, y-1, down, returnSize);
        }
    }
    if(y+1 < matrixColSize)
    {
        if (matrix[x][y] <= matrix[x][y+1] && (map[x][y]|map[x][y+1])>map[x][y+1] )
        {
            map[x][y+1] |= map[x][y];
            fromfrom(matrix, matrixRowSize, matrixColSize, map, x, y+1, down, returnSize);
        }
    }

    return map[x][y];
}
int **pacificAtlantic(int **matrix, int matrixRowSize, int matrixColSize, int **columnSizes, int *returnSize)
{
    *returnSize = 0;
    unsigned char **map = (unsigned char **)malloc(sizeof(unsigned char *) * matrixRowSize);
    for (int i = 0; i < matrixRowSize; i++)
    {
        map[i] = (unsigned char *)malloc(sizeof(unsigned char) * matrixColSize);
        memset(map[i], 0, (size_t)matrixColSize);
        map[i][0] |= pacific;
        map[i][matrixColSize-1] |= atlantic;
    }
    for (int j = 0; j < matrixColSize; j++)
    {
        map[0][j] |= pacific;
        map[matrixRowSize-1][j] |= atlantic;
    }

    for (int i = 0; i < matrixRowSize; i++)
    {
        fromfrom(matrix, matrixRowSize, matrixColSize, map, i, 0, 0, returnSize);
        fromfrom(matrix, matrixRowSize, matrixColSize, map, i, matrixColSize-1, 0, returnSize);
    }
    for (int j = 0; j < matrixColSize; j++)
    {
        fromfrom(matrix, matrixRowSize, matrixColSize, map, 0, j, 0, returnSize);
        fromfrom(matrix, matrixRowSize, matrixColSize, map, matrixRowSize-1, j, 0, returnSize);
    }
    int **ret = (int **)malloc(sizeof(int *) * (matrixRowSize*matrixColSize));
    int *retcs = (int *)malloc(sizeof(int) * (matrixRowSize*matrixColSize));
    int k = 0;
    for (int i = 0; i < matrixRowSize; i++)
    {
        for (int j = 0; j < matrixColSize; j++)
        {
            if (both(map[i][j]))
            {
                ret[k] = (int *)malloc(sizeof(int) * 2);
                ret[k][0] = i;
                ret[k][1] = j;
                retcs[k] = 2;
                k++;
            }
        }
    }
    *returnSize = k;
    *columnSizes = retcs;
    return ret;
}
unsigned char gogo(int **matrix, int matrixRowSize, int matrixColSize, unsigned char **map, int x, int y, int from, int *returnSize)
{
    if (map[x][y])
    {
        return map[x][y];
    }
    printf("compute one (%d, %d)\n", x, y);
    if (x == 0)
    {
        map[x][y] = map[x][y] | pacific;
    }
    else
    {
        if (matrix[x][y] >= matrix[x - 1][y] && from!=up)
        {
            map[x][y] |= gogo(matrix, matrixRowSize, matrixColSize, map, x - 1, y, down, returnSize);
        }
    }
    if (x == (matrixRowSize - 1))
    {
        map[x][y] = map[x][y] | atlantic;
    }
    else
    {
        if (matrix[x][y] >= matrix[x + 1][y] && from!=down)
        {
            map[x][y] |= gogo(matrix, matrixRowSize, matrixColSize, map, x + 1, y, up, returnSize);
        }
    }
    if (y == 0)
    {
        map[x][y] = map[x][y] | pacific;
    }
    else
    {
        if (matrix[x][y] >= matrix[x][y - 1] && from != right)
        {
            map[x][y] |= gogo(matrix, matrixRowSize, matrixColSize, map, x, y - 1, left, returnSize);
        }
    }
    if (y == (matrixColSize - 1))
    {
        map[x][y] = map[x][y] | atlantic;
    }
    else
    {
        if (matrix[x][y] >= matrix[x][y + 1]  && from != left )
        {
            map[x][y] |= gogo(matrix, matrixRowSize, matrixColSize, map, x, y + 1,right, returnSize);
        }
    }
    if (map[x][y] == 0)
    {
        map[x][y] = land;
    }
    else if ( both(map[x][y]) && ((map[x][y] & counted) != counted))
    {
        *returnSize += 1;
        map[x][y] |= counted;
    }
    return map[x][y];
}
int **pacificAtlantic1(int **matrix, int matrixRowSize, int matrixColSize, int **columnSizes, int *returnSize)
{
    *returnSize = 0;
    unsigned char **map = (unsigned char **)malloc(sizeof(unsigned char *) * matrixRowSize);
    for (int i = 0; i < matrixRowSize; i++)
    {
        map[i] = (unsigned char *)malloc(sizeof(unsigned char) * matrixColSize);
        memset(map[i], 0, (size_t)matrixColSize);
    }
    for (int i = 0; i < matrixRowSize; i++)
    {
        for (int j = 0; j < matrixColSize; j++)
        {
            gogo(matrix, matrixRowSize, matrixColSize, map, i, j, 0, returnSize);
        }
    }
    int **ret = (int **)malloc(sizeof(int *) * (*returnSize));
    int *retcs = (int *)malloc(sizeof(int) * (*returnSize));
    int k = 0;
    for (int i = 0; i < matrixRowSize; i++)
    {
        for (int j = 0; j < matrixColSize; j++)
        {
            if (both(map[i][j]))
            {
                ret[k] = (int *)malloc(sizeof(int) * 2);
                ret[k][0] = i;
                ret[k][1] = j;
                retcs[k] = 2;
                k++;
            }
        }
    }
    *columnSizes = retcs;
    return ret;
}
#if 0
int main()
{
    const int x = 5;
    const int y = 5;
    int data[x][y] = {{1, 2, 2, 3, 5}, {3, 2, 3, 4, 4}, {2, 4, 5, 3, 1}, {6, 7, 1, 4, 5}, {5, 1, 1, 2, 4}};
    int** matrix = (int**)malloc(sizeof(int*)*x);
    for(int i=0;i<x;i++){
        matrix[i] = data[i];
    }
    int *columnSizes;
    int returnSize;
    int** ret = pacificAtlantic(matrix, x, y, &columnSizes, &returnSize);
    for (int i = 0; i < returnSize; i++)
    {
        printf("x=%d, y=%d\n", ret[i][0], ret[i][1]);
    }

    return 0;
}
#endif






















































