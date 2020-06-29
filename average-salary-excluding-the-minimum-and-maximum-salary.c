int cmp(const void*a, const void*b){ return(*(int*)a-*(int*)b);}

double average(int*A, int Asz){
  int i;
  int N = Asz;
  int cnt = 0;
  double sm = 0;
  qsort(A, Asz, sizeof(int), cmp);
  for(i=1; i<N-1; i++){
    cnt++;
    sm += A[i];
  }
  return sm / cnt;
}
