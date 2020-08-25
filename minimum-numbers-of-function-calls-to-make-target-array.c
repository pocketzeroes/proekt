inline int max_L(int a, int b){
  return a>=b?a:b;
}
int minOperations(int*A, int Asz){
  int i;
  int res = 0;
  int mx;
  int N = Asz;
  {
    int Lj4PdHRW;
    int KL2GvlyY;
    if(N==0)
      KL2GvlyY = 0;
    else{
      KL2GvlyY = A[0];
      for(Lj4PdHRW=(1);Lj4PdHRW<(N);Lj4PdHRW++)
        KL2GvlyY = max_L(KL2GvlyY, A[Lj4PdHRW]);
    }
    mx =KL2GvlyY;
  }
  while(mx > 1){
    int i;
    for(i=(0);i<(N);i++)
      res += A[i] % 2;
    for(i=(0);i<(N);i++)
      A[i] /= 2;
    mx /= 2;
    res++;
  }
  for(i=(0);i<(N);i++)
    res += A[i];
  return res;
}
