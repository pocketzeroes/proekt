int countBattleships(char** board, int boardRowSize, int boardColSize) {
    if (boardRowSize==0 ||boardColSize==0) {
        return 0;
    }
    int cnt = 0;
    for (int i = 0; i < boardRowSize; ++i) {
        for (int j = 0; j < boardColSize; ++j) {
            cnt += board[i][j] == 'X' &&
                   (i == 0 || board[i - 1][j] != 'X') &&
                   (j == 0 || board[i][j - 1] != 'X');
        }
    }
    return cnt;
}
