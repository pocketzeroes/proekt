int cmp(const void * a, const void * b){  return ( *(int*)a - *(int*)b );}

int*sortedSquares(int*A, int Asz, int*rsz){
    for(int i=0;i < Asz; i++)
      A[i] = A[i] * A[i];
    qsort(A, Asz, sizeof(int), cmp);
   *rsz = Asz;
    return A;
}
