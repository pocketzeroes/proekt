
int Digit_L(int n){
  int res = 0;
  while(n){
    res++;
    n /= 10;
  }
  return res;
}
int chmin(int*a, int b){
  if(*a>b){
    *a=b;
  }
  return *a;
}


int dig(int n){
  if(n<=1){
    return 0;
  }
  return Digit_L(n);
}

int getLengthOfOptimalCompression(char*s, int k){
  int i, j, x, us, z;
  int dp[101][101]={};
  int n = strlen(s);
  for(i=(0);i<(n);i++){
    for(j=(0);j<(k+1);j++){
      dp[i+1][j] = 1073709056;
    }
  }
  for(i=(0);i<(n);i++){
    for(j=(0);j<(k+1);j++){
      if(j+1 <= k){
        chmin(&dp[i+1][j+1], dp[i][j]);
      }
      us = z = 0;
      for(x=(i);x<(n);x++){
        if(s[i]==s[x]){
          z++;
        }
        else{
          us++;
        }
        if(j+us <= k){
          chmin(&dp[x+1][j+us], dp[i][j] + 1 + dig(z));
        }
      }
    }
  }
  return dp[n][k];
}

