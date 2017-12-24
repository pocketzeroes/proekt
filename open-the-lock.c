static bool visit[10005];
static int  dist [10005];
static int  Q    [10005];

int openLock(char**deadends, int deadSz, char*target){
    memset(visit, 0, sizeof(visit));
    memset(dist,  0, sizeof(dist ));
    for(int z=0;z<deadSz;z++){char*s = deadends[z];
        int x = 0;
        sscanf(s, "%d", &x);
        visit[x] = 1;
    }
    if (visit[0])
        return -1;
    int s = 0, t = 1;
    Q    [1] = 0;
    visit[0] = 1;
    dist [0] = 0;
    while (s < t) {
        int x = Q[++s];
        int nums[4];
        nums[0] =  x % 10;
        nums[1] = (x / 10) % 10;
        nums[2] = (x / 100) % 10;
        nums[3] =  x / 1000;
        int y;
        for (int i = 0; i < 4; i++) {
            nums[i] = (nums[i] + 1) % 10;
            y = nums[3] * 1000 + nums[2] * 100 + nums[1] * 10 + nums[0];
            if(!visit[y]) {
                visit[y] = 1;
                dist [y] = dist[x] + 1;
                Q  [++t] = y;
            }
            nums[i] = (nums[i] - 2 + 10) % 10;
            y = nums[3] * 1000 + nums[2] * 100 + nums[1] * 10 + nums[0];
            if(!visit[y]) {
                visit[y] = 1;
                dist [y] = dist[x] + 1;
                Q  [++t] = y;
            }
            nums[i] = (nums[i] + 1) % 10;
        }
    }
    int T = 0;
    sscanf(target, "%d", &T);
    return visit[T] ? dist[T] : -1;
}
