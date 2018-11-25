int cmp(const void * a, const void * b){ return ( *(int*)a - *(int*)b );}
int minIncrementForUnique(int*A, int Asz){
  if(Asz == 0)
    return 0;
  qsort(A, Asz, sizeof(int), cmp);
  int last = A[0];
  int ans = 0;
  for(int i=1; i<Asz; i++){
    if(A[i] <= last){
      ans += last + 1 - A[i];
      last++;
    }
    else
      last = A[i];
  }
  return ans;
}
