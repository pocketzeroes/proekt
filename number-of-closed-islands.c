const int DIRS = 4;
const int DR[] = {-1,  0, +1,  0};
const int DC[] = { 0, +1,  0, -1};

int R, C;
int**grid;
bool**visited;

bool**newmat(int x, int y){
  bool**rv = calloc(x, sizeof(bool*));
  for(int i=0; i<x; i++)
    rv[i] = calloc(y, sizeof(bool));
  return rv;
}

bool valid(int r, int c) {
    return 0 <= r && r < R && 0 <= c && c < C;
}
bool dfs(int r, int c) {
    if (visited[r][c])
        return false;
    visited[r][c] = true;
    bool can_exit = false;
    for (int dir = 0; dir < DIRS; dir++) {
        int nr = r + DR[dir];
        int nc = c + DC[dir];
        if (valid(nr, nc)) {
            if (grid[nr][nc] == 0) {
                bool option = dfs(nr, nc);
                can_exit = can_exit || option;
            }
        }
        else {
            can_exit = true;
        }
    }
    return can_exit;
}
int closedIsland(int**_grid, int gridSz, int*grid0sz){
    grid = _grid;
    R = gridSz;
    C = gridSz==0 ? 0 : grid0sz[0];
    visited = newmat(R, C);//of bool
    int answer = 0;
    for(int r = 0; r < R; r++)
        for(int c = 0; c < C; c++)
            if(grid[r][c] == 0 && !visited[r][c])
                answer += dfs(r, c) ? 0 : 1;
    return answer;
}
