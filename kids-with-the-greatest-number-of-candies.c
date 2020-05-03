
bool*kidsWithCandies(int*A, int Asz, int D, int*rsz){
  int i;
  int N = Asz;
  int mx;
  bool*res = calloc(N, sizeof(bool));
  {
    int Lj4PdHRW;
    int KL2GvlyY;
    if(N==0)
      KL2GvlyY = 0;
    else{
      KL2GvlyY = A[0];
      for(Lj4PdHRW=(1);Lj4PdHRW<(N);Lj4PdHRW++)
        KL2GvlyY = fmax(KL2GvlyY, A[Lj4PdHRW]);
    }
    mx =KL2GvlyY;
  }
  for(i=0; i<N; i++)
    res[i]=( A[i]+D >= mx );
 *rsz=N;
  return res;
}
