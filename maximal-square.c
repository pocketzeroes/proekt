char **grid;
int check(int i, int j, int k)
{
    int x;
    int y;
    for(x=i; x<=i+k; x++)
    {
        for(y=j; y<=j+k; y++)
        {
            if(grid[x][y] == '0')
                return 0;
        }
    }
    return 1;
}
int get_max_square(int row, int col)
{
    int max;
    int i;
    int j;
    int k;
    max = 0;
    for(i=0; i<row; i++)
    {
        for(j=0; j<col; j++)
        {
            if(grid[i][j] == '1')
            {
                if(max > 0)
                    k = max;
                else
                    k = 1;
                while(1)
                {
                   if(check(i,j,k))
                   {
                       k++;
                   }
                   else
                        break; 
                }
                if(k > max)
                    max = k;
            }
        }
    }
    return max*max;
}
void init(char **matrix, int row, int col)
{
    int i;
    int j;
    grid = (char**) malloc((row+1)*sizeof(char*));
    if(!grid)
    {
        exit(1);
    }
    for(i=0; i<row+1; i++)
    {
        grid[i] = (char*) malloc(col+1);
        memset(grid[i], '0', col+1);
    }
    for(i=0; i<row; i++)
        for(j=0; j<col; j++)
            grid[i][j] = matrix[i][j];
}
void destroy(int row, int col)
{
    int i;
    for(i=0; i<row+1; i++)
        free(grid[i]);
    free(grid);
}
int maximalSquare(char **matrix, int matrixRowSize, int matrixColSize) 
{
    int max_square;
    if(matrixRowSize == 0 || matrixColSize == 0)
        return 0;
    init(matrix, matrixRowSize, matrixColSize);
    max_square = get_max_square(matrixRowSize, matrixColSize);
    destroy(matrixRowSize, matrixColSize);
    return max_square;
}


















































