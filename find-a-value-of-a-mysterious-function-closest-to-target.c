
int chmin(int*a, int b){
  if(*a>b)
     *a=b;
  return a;
}

int nxt[20][100000+2];

int closestToTarget(int*A, int Asz, int target){
  int i, j;
  int res = 1073709056;
  int n = Asz;
  int now;
  int p;
  int nx;
  for(j=0; j<20; j++)
    nxt[j][n] = n;
  for(i=(n)-1;i>=(0);i--){
    for(j=(0);j<(20);j++)
      nxt[j][i] = nxt[j][i+1];
    for(j=(0);j<(20);j++)
      if(!((A[i]) &(1<<(j))))
        nxt[j][i] = i;
  }
  for(i=0; i<n; i++){
    p = i;
    now = (1<<25)-1;
    while(p < n){
      now &= A[p];
      chmin(&res, abs(target-now));
      nx = n;
      for(j=0; j<20; j++)
        if(((now) &(1<<(j))))
          chmin(&nx, nxt[j][p+1]);
      p = nx;
    }
  }
  return res;
}
