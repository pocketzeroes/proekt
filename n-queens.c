typedef struct Solutions
{
    int size;
    int capacity;
    int n;
    char*** solutions;
}Solutions;

void initSolutions(Solutions* solutions, int initCapacity, int n)
{
    solutions->solutions = (char***)malloc(initCapacity * sizeof(char**));
    solutions->size      = 0;
    solutions->capacity  = initCapacity;
    solutions->n         = n;
}

void pushBack(Solutions* solutions, int* columns)
{
    int newSize = solutions->size + 1;
    if (newSize > solutions->capacity)
    {
        solutions->capacity *= 2;
        solutions->solutions = (char***)realloc(solutions->solutions, solutions->capacity * sizeof(char**));
    }
    solutions->solutions[newSize - 1] = (char**)malloc(solutions->n * sizeof(char*));
    for (int i = 0; i != solutions->n; ++i)
    {
        solutions->solutions[newSize - 1][i] = (char*)malloc((solutions->n + 1)*sizeof(char));
        solutions->solutions[newSize - 1][i][solutions->n] = '\0';
        for (int j = 0; j != solutions->n; ++j)
            solutions->solutions[newSize - 1][i][j] = '.';
        solutions->solutions[newSize - 1][i][columns[i]] = 'Q';
    }
    solutions->size = newSize;
}

bool CheckIfValid(int* columns, int row, int col)
{
    for (int x = 0; x != row; ++x)
    {
        int y = columns[x];
        if (col == y)
            return false;
        int colDistance = labs(y - col);
        int rowDistance = row - x;
        if (colDistance == rowDistance)
            return false;
    }
    return true;
}

void PlaceQueen(int n, int row, int* columns, Solutions* solutions, int* returnSize)
{
    if (row == n)
    {
        pushBack(solutions, columns);
        *returnSize = solutions->size;
    }
    else
    {
        for (int col = 0; col != n; ++col)
        {
            if (CheckIfValid(columns, row, col))
            {
                columns[row] = col;
                PlaceQueen(n, row + 1, columns, solutions, returnSize);
            }
        }
    }
}

char*** solveNQueens(int n, int* returnSize)
{
    *returnSize = 0;
    Solutions solutions;
    initSolutions(&solutions, 2, n);
    if (n <= 0)
        return solutions.solutions;
    int* columns = (int*)malloc(n * sizeof(int));
    for (int i = 0; i != n; ++i)
        columns[i] = -1;
    PlaceQueen(n, 0, columns, &solutions, returnSize);
    free(columns);
    return solutions.solutions;
}




































