#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
int**newmat(int x, int y){
  int**rv = calloc(x, sizeof(int*));
  for(int i=0; i<x; i++)
    rv[i] = calloc(y, sizeof(int));
  return rv;
}
void freemat(int**m, int x){
  for(int i=0; i<x; i++)
    free(m[i]);
  free(m);
  m = NULL;
}

enum{MD = 1000000007};
void *wmem;
char memarr[96000000];

//struct AhoCorasick_Sum{
int node;
int mem;
int alphabet;
int **nx;
int   nxSz;
int *failed;
int *sum;

void init(){
  int i;
  node = 1;
  for(i=(0);i<(alphabet);i++)
    nx[0][i] = -1;
  failed[0] = 0;
  sum[0] = 0;
}
void mmalloc(const int n, const int k){
  int i;
  nx = newmat(n, k);
  nxSz = n;
  failed = calloc(n, sizeof(int));
  sum    = calloc(n, sizeof(int));
  node = n;
  alphabet = k;
  init();
}
void mfree(){
  freemat(nx, nxSz);
  free(failed);
  free(sum);
}
void addWord(const int word[], const int len, int val){
  int i;
  int j;
  int k;
  int now = 0;
  for(i=(0);i<(len);i++){
    if(nx[now][word[i]]==-1){
      k = node++;
      nx[now][word[i]] = k;
      for(j=(0);j<(alphabet);j++)
        nx[k][j] = -1;
      sum[k] = 0;
    }
    now = nx[now][word[i]];
  }
  sum[now] += val;
}
void construct(){
  void*mem = wmem;
  int i;
  int j;
  int k;
  int now;
  int *q;
  int qs;
  int qe;
  q = (int*) mem;
  qs = qe = 0;
  now = 0;
  for(k=(0);k<(alphabet);k++){
    if(nx[now][k] != -1){
      q[qe++] = nx[now][k];
      failed[ nx[now][k] ] = now;
    }
  }
  while(qs < qe){
    now = q[qs++];
    for(k=(0);k<(alphabet);k++){
      if(nx[now][k] != -1){
        i = failed[now];
        while(i){
          if(nx[i][k] != -1)
            break;
          i = failed[i];
        }
        if(nx[i][k] != -1)
          i = nx[i][k];
        failed[ nx[now][k] ] = i;
        sum[ nx[now][k] ] += sum[i];
        q[qe++] = nx[now][k];
      }
    }
  }
}
int next(const int n, const int c){
  int i;
  int now;
  now = n;
  if(nx[n][c]!=-1)
    return nx[n][c];
  while(now && nx[now][c]==-1)
    now=failed[now];
  if(nx[now][c]!=-1)
    now = nx[now][c];
  return nx[n][c] = now;
}
//};

int dp[501][2][2][51];

int findGoodStrings(int n, char*s1, char*s2, char*evil){
  clr(dp);
  clr(memarr);
  int i, x;
  wmem = memarr;
  int m = strlen(evil);
  int e[51];
  int st;
  int ed;
  int sx;
  int sy;
  int sj;
  int res = 0;
  node=mem=alphabet=0;
  for(i=0;i<n;i++)
    s1[i] -= 'a';
  for(i=0;i<n;i++)
    s2[i] -= 'a';
  for(i=0;i<m;i++)
    e[i] = evil[i] - 'a';
  mmalloc(m+1, 26);
  init();
  addWord(e, m, 1);
  construct();
  m = node;
  for(i=0;i<n+1;i++){
    int x;
    for(x=0;x<2;x++){
      int y;
      for(y=0;y<2;y++){
        int j;
        for(j=0;j<m;j++)
          dp[i][x][y][j] = 0;
      }
    }
  }
  dp[0][0][0][0] = 1;
  for(i=0;i<n;i++){
    int x;
    for(x=0;x<2;x++){
      int y;
      for(y=0;y<2;y++){
        int j;
        for(j=0;j<m;j++){
          int k;
          if(x)
            st =0;
          else
            st =s1[i];
          if(y)
            ed =25;
          else
            ed =s2[i];
          for(k=st;k<ed+1;k++){
            sj = next(j, k);
            if(sum[sj])
              continue;
            if(k > s1[i])
              sx =1;
            else
              sx =x;
            if(k < s2[i])
              sy =1;
            else
              sy =y;
            dp[i+1][sx][sy][sj] += dp[i][x][y][j];
            dp[i+1][sx][sy][sj] %= MD;
          }
        }
      }
    }
  }
  for(x=0;x<2;x++){
    int y;
    for(y=0;y<2;y++){
      int j;
      for(j=0;j<m;j++){
        res += dp[n][x][y][j];
        res %= MD;
      }
    }
  }
  mfree();
  return res;
}
