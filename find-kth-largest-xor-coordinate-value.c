enum{m = 1048576};
int cnt[m];

int kthLargestValue(int**A, int Asz, int*A0sz, int k){
  int i;
  int j;
  int X = Asz;
  int Y = A0sz[0];
  for(i=(0);i<(m);i++){
    cnt[i] = 0;
  }
  for(i=(0);i<(X);i++){
    for(j=(0);j<(Y);j++){
      if(i){
        A[i][j] ^= A[i-1][j];
      }
      if(j){
        A[i][j] ^= A[i][j-1];
      }
      if(i && j){
        A[i][j] ^= A[i-1][j-1];
      }
      cnt[A[i][j]]++;
    }
  }
  k--;
  for(i=(m)-1;i>=(0);i--){
    if(cnt[i] > k){
      break;
    }
    k -= cnt[i];
  }
  return i;
}
