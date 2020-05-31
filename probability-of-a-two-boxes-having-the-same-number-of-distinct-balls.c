int C;
int A[9];
double dp[9][9][9][25][25];
double comb[50][50];

double solve(int dep, int d1, int d2, int r1, int r2){
  double res = 0;
  double p;
  if(dp[dep][d1][d2][r1][r2] >= 0){
    return dp[dep][d1][d2][r1][r2];
  }
  if(dep == C){
    if(d1==d2){
      res++;
    }
  }
  else{
    int i;
    for(i=(0);i<(A[dep]+1);i++){
      if(i > r1 || A[dep]-i > r2){
        continue;
      }
      p = comb[r1][i] * comb[r2][A[dep]-i] / comb[r1+r2][A[dep]];
      if(i){
        if(i!=A[dep]){
          res += p * solve(dep+1, d1+1, d2+1, r1-i, r2-(A[dep]-i));
        }
        else{
          res += p * solve(dep+1, d1+1, d2+0, r1-i, r2-(A[dep]-i));
        }
      }
      else{
        if(i!=A[dep]){
          res += p * solve(dep+1, d1+0, d2+1, r1-i, r2-(A[dep]-i));
        }
        else{
          res += p * solve(dep+1, d1+0, d2+0, r1-i, r2-(A[dep]-i));
        }
      }
    }
  }
  return dp[dep][d1][d2][r1][r2] = res;
}
double getProbability(int*A__, int A__sz){
  int i, x;
  C = A__sz;
  for(i=(0);i<(C);i++){
    A[i] = A__[i];
  }
  int cTE1_r3A;
  int RZTsC2BF;
  if(C==0){
    RZTsC2BF = 0;
  }
  else{
    RZTsC2BF = A[0];
    for(cTE1_r3A=(1);cTE1_r3A<(C);cTE1_r3A++){
      RZTsC2BF += A[cTE1_r3A];
    }
  }
  int N = RZTsC2BF;
  for(i=(0);i<(50);i++){
    comb[i][0] = 1;
  }
  for(i=(1);i<(50);i++){
    int j;
    for(j=(1);j<(50);j++){
      comb[i][j] = comb[i-1][j-1] + comb[i-1][j];
    }
  }
  for(x=(0);x<(9);x++){
    for(i=(0);i<(9);i++){
      int j;
      for(j=(0);j<(9);j++){
        int k;
        for(k=(0);k<(25);k++){
          int l;
          for(l=(0);l<(25);l++){
            dp[x][i][j][k][l] = -1;
          }
        }
      }
    }
  }
  return solve(0,0,0,N/2,N/2);
}
