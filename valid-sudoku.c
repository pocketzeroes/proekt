bool anyDuplicate(char**board, int start_row, int end_row, int start_col, int end_col) {
    bool is_present[9]={false};
    for (int i = start_row; i < end_row; ++i) 
        for (int j = start_col; j < end_col; ++j) 
            if (board[i][j] != '.') {
                if (is_present[board[i][j] - '1'])
                    return true;
                is_present[board[i][j] - '1'] = !is_present[board[i][j] - '1'];
            }
    return false;
}

bool isValidSudoku(char** board, int boardRowSize, int boardColSize){
    for (int i = 0; i < 9; ++i)
        if (anyDuplicate(board, i, i + 1, 0, 9))
            return false;
    for (int j = 0; j < boardRowSize; ++j)
        if (anyDuplicate(board, 0, 9, j, j + 1))
            return false;
    for (int i = 0; i < 9; i += 3)
        for (int j = 0; j < 9; j += 3)
            if (anyDuplicate(board, i, i + 3, j, j + 3))
                return false;
    return true;
}


