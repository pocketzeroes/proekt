int max(int a,int b){return a>b?a:b;}

typedef struct pair{
    int first;
    int second;
}pair;
pair newPair(int a, int b){
    pair rez;
    rez.first =a;
    rez.second=b;
    return rez;
}

enum{ MOD  =(int) 1e9+7};
enum{ SIZE =(int) 55   };
bool u[SIZE][SIZE];
int an;
int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};
pair bfs[SIZE*SIZE];

void f(int x, int y, int n, int m, int**grid){
    bfs[0] = newPair(x,y);
    u[x][y] = 1;
    int rr = 1;
    for (int i = 0; i < rr; ++i){
        for (int k = 0; k < 4; ++k){
            int nx = bfs[i].first +dx[k];
            int ny = bfs[i].second+dy[k];
            if(nx<0||ny<0||nx>=n||ny>=m||grid[nx][ny]!=1||u[nx][ny])
                continue;
            u[nx][ny]=1;
            bfs[rr++]=newPair(nx,ny);
        }
    }
    an = max(an, rr);
}
int maxAreaOfIsland(int**grid, int gridSz, int grid0sz){
    int n = gridSz;
    if(!n)
        return 0;
    an = 0;
    int m = grid0sz;
    memset((u), 0, sizeof((u)));
    for (int i = 0; i < (n); ++i)
        for (int j = 0; j < (m); ++j){
            if(grid[i][j]==1&&!u[i][j])
                f(i, j, n, m, grid);
        }
    return an;
}



















