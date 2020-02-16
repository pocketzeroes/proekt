int countNegatives(int**A, int Asz, int*A0sz){
  int i;
  int res = 0;
  for(i=0;i<Asz;i++){
    int j;
    for(j=0;j<A0sz[0];j++){
      if(A[i][j] < 0)
        res++;
    }
  }
  return res;
}
