double dp[111][30][30];
int n;
int dx[8]={2,2,1,1,-1,-1,-2,-2};
int dy[8]={1,-1,2,-2,2,-2,1,-1};

bool Out(int x,int y){
    return x<0||y<0 || x>=n||y>=n;
}
double knightProbability(int N, int K, int r, int c) {
   n=N;
   memset((dp), 0, sizeof((dp)));
   for (int i = 0; i < (N); ++i)
       for (int j = 0; j < (N); ++j)
           dp[0][i][j]=1;
   for (int lv = (1); lv < (K+1); ++lv){
        for (int x = 0; x < (N); ++x){
            for (int y = 0; y < (N); ++y){
                for (int k = 0; k < (8); ++k){
                    int nx=x+dx[k];
                    int ny=y+dy[k];
                    if(!Out(nx,ny))
                        dp[lv][x][y]+=dp[lv-1][nx][ny]/8.;
                }
            }
        }
   }
   return dp[K][r][c];
}
