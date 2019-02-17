int orangesRotting(int**grid, int gridSz, int*grid0sz){
    int R = gridSz;
    int C = R == 0 ? 0 : grid0sz[0];
    int minutes = 0;
    while (true) {
        bool fresh = false;
        for (int r = 0; r < R; r++)
            for (int c = 0; c < C; c++)
                if (grid[r][c] == 1)
                    fresh = true;
        if (!fresh)
            return minutes;
        for (int r = 0; r < R; r++)
            for (int c = 0; c < C; c++)
                if (grid[r][c] == 1) {
                    bool has_rotten = false;
                    has_rotten |= r > 0 && grid[r - 1][c] == 2;
                    has_rotten |= c > 0 && grid[r][c - 1] == 2;
                    has_rotten |= r + 1 < R && grid[r + 1][c] == 2;
                    has_rotten |= c + 1 < C && grid[r][c + 1] == 2;
                    if (has_rotten)
                        grid[r][c] = 3;
                }
        bool any = false;
        for (int r = 0; r < R; r++)
            for (int c = 0; c < C; c++)
                if (grid[r][c] == 3) {
                    grid[r][c] = 2;
                    any = true;
                }
        if (!any)
            return -1;
        minutes++;
    }
}
