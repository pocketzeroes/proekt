enum{ N = 8};
const int DR[] = {-1, 0, +1, 0};
const int DC[] = {0, +1, 0, -1};

int numRookCaptures(char** board, int boardRowSize, int *boardColSizes) {
    int row = -1, col = -1;
    for (int r = 0; r < N; r++)
        for (int c = 0; c < N; c++)
            if (board[r][c] == 'R') {
                row = r;
                col = c;
            }
    int pawns = 0;
    for (int dir = 0; dir < 4; dir++) {
        int r = row, c = col;
        while (true) {
            r += DR[dir];
            c += DC[dir];
            if (r < 0 || r >= 8 || c < 0 || c >= 8)
                break;
            if (board[r][c] == 'B')
                break;
            if (board[r][c] == 'p') {
                pawns++;
                break;
            }
        }
    }
    return pawns;
}
