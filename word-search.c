bool isFound(char** board, int row, int col, char*word, int rIndex, int cIndex)
{
    if(*word == '\0') return true; 
    if(rIndex>=row || cIndex>=col || rIndex<0 || cIndex<0 || *word!=board[rIndex][cIndex]) return false;
    char t = board[rIndex][cIndex];
    board[rIndex][cIndex] = '\0'; 
    if(isFound(board, row, col, word+1, rIndex+1, cIndex) || 
       isFound(board, row, col, word+1, rIndex-1, cIndex) || 
       isFound(board, row, col, word+1, rIndex, cIndex+1) || 
       isFound(board, row, col, word+1, rIndex, cIndex-1)) 
             return true;
    board[rIndex][cIndex] = t; 
    return false; 
}

bool exist(char** board, int row, int col, char* word) 
{
    for(int i = 0; i < row; i++)
        for(int j = 0; j < col; j++)
            if(isFound(board, row, col, word, i, j))
                return true;
    return false;
}

