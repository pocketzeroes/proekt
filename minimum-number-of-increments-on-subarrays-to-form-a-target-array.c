
int minNumberOperations(int*A, int Asz){
  int i;
  int N = Asz;
  int res = A[0];
  for(i=(1);i<(N);i++){
    res += fmax(0, A[i]-A[i-1]);
  }
  return res;
}
