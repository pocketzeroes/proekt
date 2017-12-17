int a[55][55];
int visit[55][55];
int n, m;
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};
const int d_op[4] = {2, 3, 0, 1};
bool hasWall[55][55][4];


int dfs(int x, int y, int visitId) {
    if (visit[x][y] == visitId)
        return 0;
    if (!a[x][y])
        return visit[x][y] = visitId, 1;
    visit[x][y] = visitId;
    int ret = 0;
    for (int id = 0; id < 4; id++) {
        if (hasWall[x][y][id]) continue;
        int x1 = x + dx[id];
        int y1 = y + dy[id];
        if (x1 >= 0 && x1 < n && y1 >= 0 && y1 < m) {
            ret += dfs(x1, y1, visitId);
        }
    }
    return ret;
}
int addWalls(int visitId) {
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (visit[i][j] == visitId && a[i][j]) {
                for (int id = 0; id < 4; id++) {
                    if (hasWall[i][j][id]) continue;
                    int x = i + dx[id];
                    int y = j + dy[id];
                    if (x >= 0 && x < n && y >= 0 && y < m) {
                        if (a[x][y] == 0) {
                            hasWall[i][j][id] = 1;
                            hasWall[x][y][d_op[id]] = 1;
                            ++ans;
                        }
                    }
                }
            }
        }
    }
    return ans;
}
void spread() {
    int affected[55][55];
    memset(affected, 0, sizeof(affected));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i][j]) {
                for (int id = 0; id < 4; id++) {
                    if (hasWall[i][j][id]) continue;
                    int x = i + dx[id];
                    int y = j + dy[id];
                    if (x >= 0 && x < n && y >= 0 && y < m) {
                        if (a[x][y] == 0) {
                            affected[x][y] = 1;
                        }
                    }
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            a[i][j] |= affected[i][j];
        }
    }
}
int containVirus(int**grid, int gridSz, int grid0sz){
    n = gridSz;
    m = grid0sz;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            a[i][j] = grid[i][j];
        }
    }
    int ans = 0;
    memset(hasWall, 0, sizeof(hasWall));
    while (1) {
        memset(visit, 0, sizeof(visit));
        int maxCnt = -1;
        int x0 = 0, y0 = 0;
        int visitId = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (!visit[i][j] && a[i][j]) {
                    int cnt = dfs(i, j, ++visitId);
                    if (cnt > maxCnt) {
                        maxCnt = cnt;
                        x0 = i, y0 = j;
                    }
                }
            }
        }
        if (maxCnt <= 0) {
            break;
        }
        ans += addWalls(visit[x0][y0]);
        spread();
    }
    return ans;
}
