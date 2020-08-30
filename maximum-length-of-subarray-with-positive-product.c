#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)

int chmax(int*a, int b){
  if(*a<b){
    *a=b;
  }
  return *a;
}

int N;
int A[100000];

int solve(int N, int*A){
  int i;
  int res = 0;
  int f;
  int c = 1;
  for(i=0; i<N; i++){
    if(A[i] < 0){
      f = i;
      break;
    }
  }
  if(i==N)
    return N;
  for(i=0; i<N; i++){
    c *= A[i];
    if(c == 1)
      chmax(&res, i+1);
    if(c ==-1)
      chmax(&res, i-f);
  }
  return res;
}
int getMaxLen(int*num, int numSz){
  clr(A);
  int i;
  int res = 0;
  N = 0;
  for(i=0; i<=numSz; i++){
    int ni;
    if(i==numSz)
      ni=0;
    else
      ni=num[i];
    if(ni==0){
      chmax(&res, solve(N, A));
      N = 0;
      continue;
    }
    if(ni > 0)
      A[N++] =1;
    else
      A[N++] =-1;
  }
  return res;
}
