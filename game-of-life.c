#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

void gameOfLife(int** board, int boardRowSize, int boardColSize) {
    int m = boardRowSize, n = boardColSize;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            int count = 0;
            for (int I = MAX(i - 1, 0); I < MIN(i + 2, m); ++I) {
                for (int J = MAX(j - 1, 0); J < MIN(j + 2, n); ++J) {
                    count += board[I][J] & 1;
                }
            }
            if ((count == 4 && board[i][j]) || count == 3) {
                board[i][j] |= 2;
            }
        }
    }
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            board[i][j] >>= 1;
        }
    }
}
