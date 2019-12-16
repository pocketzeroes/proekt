typedef struct{
  int first, second;
}pair;
pair newpair(int a, int b){
  return(pair){a,b};
}
typedef struct{
  pair first;
  int second;
}trip;
trip newtrip(pair a, int b){
  return(trip){a,b};
}
int  f[42][42][42 * 42];
trip q[42 * 42 * 42 * 42];
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

int shortestPath(int**g, int gSz, int*g0sz, int k){
    int n = gSz;
    int m = g0sz[0];
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            for(int l=0; l<=k; l++)
                f[i][j][l] = (int)1e9;
    f[0][0][0] = 0;
    q[1] = newtrip(newpair(0, 0), 0);
    for(int h=1, t=1; h<=t; h++){
        int x = q[h].first.first;
        int y = q[h].first.second;
        int l = q[h].second;
        int cur = f[x][y][l];
        for(int d=0; d<4; d++){
            int xx = x + dx[d],
                yy = y + dy[d];
            if(xx >= 0 && xx < n && yy >= 0 && yy < m){
                int l1 = l;
                if(g[xx][yy] == 1)
                    l1++;
                if(cur + 1 < f[xx][yy][l1]){
                    f[xx][yy][l1] = cur + 1;
                    q[++t] = newtrip(newpair(xx, yy), l1);
                }
            }
        }
    }
    int ans = f[n-1][m-1][0];
    for(int l=0; l<=k; l++)
       ans = fmin(ans, f[n - 1][m - 1][l]);
    if(ans > 1e8)
       ans = -1;
    return ans;
}
