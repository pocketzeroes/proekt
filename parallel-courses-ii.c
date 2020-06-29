
int chmin(int*a, int b){
  if(*a>b)
    *a=b;
  return *a;
}

int dp[1000000];
int mat[15];

int minNumberOfSemesters(int n, int**dependencies, int dependenciesSz, int*dependencies0sz, int k){
  int mask;
  int i;
  int j;
  int c;
  int rem;
  int all;
  all = (1<<n) - 1;
  for(i=(0);i<(1<<n);i++)
    dp[i] = 1073709056;
  dp[0] = 0;
  for(i=(0);i<(n);i++)
    mat[i] = 0;
  for(int z=0;z<dependenciesSz;z++){int*v = dependencies[z];
    mat[v[1]-1] |= (1 << (v[0]-1));
  }
  for(mask=(0);mask<(1<<n);mask++){
    if(dp[mask] < 1073709056){
      rem = all ^ mask;
      for(i=rem;i;i=(i-1)&rem){
        c = 0;
        for(j=(0);j<(n);j++){
          if(i & 1<<j){
            c++;
            if((mat[j] & mask) != mat[j]){
              c = -1;
              break;
            }
          }
        }
        if(c==-1 || c > k){
          continue;
        }
        chmin(&dp[mask^i], dp[mask] + 1);
      }
    }
  }
  return dp[all];
}
