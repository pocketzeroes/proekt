#ifndef STB_STRETCHY_BUFFER_H_INCLUDED
#define STB_STRETCHY_BUFFER_H_INCLUDED
#ifndef NO_STRETCHY_BUFFER_SHORT_NAMES
#define sb_free   stb_sb_free
#define sb_push   stb_sb_push
#define sb_count  stb_sb_count
#define sb_add    stb_sb_add
#define sb_last   stb_sb_last
#endif
#define stb_sb_free(a)         ((a) ? free(stb__sbraw(a)),0 : 0)
#define stb_sb_push(a,v)       (stb__sbmaybegrow(a,1), (a)[stb__sbn(a)++] = (v))
#define stb_sb_count(a)        ((a) ? stb__sbn(a) : 0)
#define stb_sb_add(a,n)        (stb__sbmaybegrow(a,n), stb__sbn(a)+=(n), &(a)[stb__sbn(a)-(n)])
#define stb_sb_last(a)         ((a)[stb__sbn(a)-1])
#define stb__sbraw(a) ((int *) (a) - 2)
#define stb__sbm(a)   stb__sbraw(a)[0]
#define stb__sbn(a)   stb__sbraw(a)[1]
#define stb__sbneedgrow(a,n)  ((a)==0 || stb__sbn(a)+(n) >= stb__sbm(a))
#define stb__sbmaybegrow(a,n) (stb__sbneedgrow(a,(n)) ? stb__sbgrow(a,n) : 0)
#define stb__sbgrow(a,n)      (*((void **)&(a)) = stb__sbgrowf((a), (n), sizeof(*(a))))

static void*stb__sbgrowf(void*arr, int increment, int itemsize){
  int dbl_cur = arr ? 2*stb__sbm(arr) : 0;
  int min_needed = stb_sb_count(arr) + increment;
  int m = dbl_cur > min_needed ? dbl_cur : min_needed;
  int*p = (int *) realloc(arr ? stb__sbraw(arr) : 0, itemsize * m + sizeof(int)*2);
  if(p){
    if(!arr)
      p[1] = 0;
    p[0] = m;
    return p+2;
  } 
  else {
    #ifdef STRETCHY_BUFFER_OUT_OF_MEMORY
    STRETCHY_BUFFER_OUT_OF_MEMORY;
    #endif
    return(void*)(2*sizeof(int));
  }
}
#endif

const int dy[] = {0, 1, 0, -1};
const int dx[] = {1, 0, -1, 0};
int H, W;

bool in(int y, int x){
  return 0 <= y && y < H && 0 <= x && x < W;
}

char dp[2][8][8][8][8];
int deg[2][8][8][8][8];

typedef struct{
  int t, i, j, y, x;
}State;

State newState(int a,int b,int c,int d,int e){
  return(State){a,b,c,d,e};
}

bool canMouseWin(char**grid, int gridSz, int catJump, int mouseJump){
  H = gridSz;
  W = strlen(grid[0]);
  memset(dp, '?', sizeof dp);
  memset(deg, 0, sizeof deg);
  for(int i=0, i_len=(H); i<i_len; ++i) for(int j=0, j_len=(W); j<j_len; ++j) if (grid[i][j] == 'F') for(int y=0, y_len=(H); y<y_len; ++y) for(int x=0, x_len=(W); x<x_len; ++x){
    for(int t=0, t_len=(2); t<t_len; ++t){
      dp[t][i][j][y][x] = 'M';
      dp[t][y][x][i][j] = 'C';
    }
  }
  for(int i=0, i_len=(H); i<i_len; ++i) for(int j=0, j_len=(W); j<j_len; ++j){
    for(int t=0, t_len=(2); t<t_len; ++t){
      dp[t][i][j][i][j] = 'C';
    }
  }
  State*E=NULL;
  for(int i=0, i_len=(H); i<i_len; ++i) for(int j=0, j_len=(W); j<j_len; ++j) if (grid[i][j] != '#'){
    for(int y=0, y_len=(H); y<y_len; ++y) for(int x=0, x_len=(W); x<x_len; ++x) if (grid[y][x] != '#'){
      for(int t=0, t_len=(2); t<t_len; ++t) if (dp[t][i][j][y][x] != '?'){
        sb_push(E, newState(t, i, j, y, x));
      }
    }
  }
  for(int i=0, i_len=(H); i<i_len; ++i) for(int j=0, j_len=(W); j<j_len; ++j) if (grid[i][j] != '#'){
    for(int y=0, y_len=(H); y<y_len; ++y) for(int x=0, x_len=(W); x<x_len; ++x){
      for(int d=0, d_len=(4); d<d_len; ++d){
        int ii = i, jj = j;
        for(int k=0, k_len=(mouseJump); k<k_len; ++k){
          ii += dy[d];
          jj += dx[d];
          if(!in(ii, jj)) 
            break;
          if(grid[ii][jj] == '#') 
            break;
          deg[0][i][j][y][x]++;
        }
      }
      deg[0][i][j][y][x]++;
    }
  }
  for(int i=0, i_len=(H); i<i_len; ++i) for(int j=0, j_len=(W); j<j_len; ++j) if (grid[i][j] != '#'){
    for(int y=0, y_len=(H); y<y_len; ++y) for(int x=0, x_len=(W); x<x_len; ++x){
      for(int d=0, d_len=(4); d<d_len; ++d) {
        int ii = i, jj = j;
        for(int k=0, k_len=(catJump); k<k_len; ++k) {
          ii += dy[d];
          jj += dx[d];
          if (!in(ii, jj))
            break;
          if (grid[ii][jj] == '#')
            break;
          deg[1][y][x][i][j]++;
        }
      }
      deg[1][y][x][i][j]++;
    }
  }
  while(sb_count(E)>0){
    State s = sb_last(E);
    stb__sbn(E)--;
    int i = s.i;
    int j = s.j;
    int y = s.y;
    int x = s.x;
    char X = dp[s.t][i][j][y][x];
    if(s.t == 0){
      deg[1][i][j][y][x]--;
      if(dp[1][i][j][y][x] == '?'){
        if(X == 'C'){
          dp[1][i][j][y][x] = 'C';
          sb_push(E, newState(1, i, j, y, x));
        }
        else if(deg[1][i][j][y][x] == 0){
          dp[1][i][j][y][x] = 'M';
          sb_push(E, newState(1, i, j, y, x));
        }
      }
      for(int d=0, d_len=(4); d<d_len; ++d){
        int yy = y;
        int xx = x;
        for(int k=0, k_len=(catJump); k<k_len; ++k) {
          yy += dy[d];
          xx += dx[d];
          if(!in(yy, xx))
            break;
          if(grid[yy][xx] == '#')
            break;
          deg[1][i][j][yy][xx]--;
          if (dp[1][i][j][yy][xx] == '?'){
            if (X == 'C'){
              dp[1][i][j][yy][xx] = 'C';
              sb_push(E, newState(1, i, j, yy, xx));
            }
            else if(deg[1][i][j][yy][xx] == 0){
              dp[1][i][j][yy][xx] = 'M';
              sb_push(E, newState(1, i, j, yy, xx));
            }
          }
        }
      }
    }
    else{
      deg[0][i][j][y][x]--;
      if (dp[0][i][j][y][x] == '?'){
        if (X == 'M') {
          dp[0][i][j][y][x] = 'M';
          sb_push(E, newState(0, i, j, y, x));
        }
        else if(deg[0][i][j][y][x] == 0){
          dp[0][i][j][y][x] = 'C';
          sb_push(E, newState(0, i, j, y, x));
        }
      }
      for(int d=0, d_len=(4); d<d_len; ++d){
        int ii = i;
        int jj = j;
        for(int k=0, k_len=(mouseJump); k<k_len; ++k){
          ii += dy[d];
          jj += dx[d];
          if(!in(ii, jj))
            break;
          if(grid[ii][jj] == '#')
            break;
          deg[0][ii][jj][y][x]--;
          if(dp[0][ii][jj][y][x] == '?') {
            if(X == 'M'){
              dp[0][ii][jj][y][x] = 'M';
              sb_push(E, newState(0, ii, jj, y, x));
            }
            else if(deg[0][ii][jj][y][x] == 0){
              dp[0][ii][jj][y][x] = 'C';
              sb_push(E, newState(0, ii, jj, y, x));
            }
          }
        }
      }
    }
  }
  int mi = -1;
  int mj = -1;
  int ci = -1;
  int cj = -1;
  for(int i=0, i_len=(H); i<i_len; ++i) for(int j=0, j_len=(W); j<j_len; ++j){
    if(grid[i][j] == 'M'){
      mi = i;
      mj = j;
    }
    if(grid[i][j] == 'C'){
      ci = i;
      cj = j;
    }
  }
  return dp[0][mi][mj][ci][cj] == 'M';
}
