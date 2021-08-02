int cmp(const void * a, const void * b){ return ( *(int*)a - *(int*)b );}
int maxIceCream(int*A, int Asz, int C){
  int i;
  int res = 0;
  qsort(A, Asz, sizeof(int), cmp);
  for(i=(0);i<(Asz);i++){
    if(C >= A[i]){
      C -= A[i];
      res++;
    }
  }
  return res;
}
