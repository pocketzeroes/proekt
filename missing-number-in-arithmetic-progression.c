int missingNumber(int*A, int Asz){
  int i;
  int d;
  int N = Asz;
  d = (A[N-1] - A[0]) / N;
  for(i=(0);i<(N);i++){
    if(A[i] != A[0] + d * i){
      return A[0] + d * i;
    }
  }
  return A[0];
}
