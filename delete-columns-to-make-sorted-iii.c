inline int min(int a,int b){return a<b?a:b;}
void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}

enum{ INF =(int) 1e9 + 5};
int R, C;
char**A;

bool valid(int col1, int col2) {
  assert(col1 <= col2);
  if (col1 <= 0)
    return true;
  col1--; col2--;
  for (int r = 0; r < R; r++)
    if (A[r][col1] > A[r][col2])
      return false;
  return true;
}
int minDeletionSize(char**pA, int Asz){
  A = pA;
  R = Asz;
  C = strlen(A[0]);
  int dp[C+1];
  fill(dp, C+1, INF);
  dp[0] = 0;
  for (int i = 1; i <= C; i++)
    for (int j = 0; j < i; j++)
      if (valid(j, i))
        dp[i] = min(dp[i], dp[j] + i - j - 1);
  int best = INF;
  for (int i = 0; i <= C; i++)
    best = min(best, dp[i] + C - i);
  return best;
}
