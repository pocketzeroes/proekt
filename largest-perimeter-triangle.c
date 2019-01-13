int cmp(const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}
int largestPerimeter(int*A, int Asz){
    qsort(A, Asz, sizeof(int), cmp);
    int bval = 0;
    for (int i = 0; i + 2 < Asz; i++){
        if (A[i] + A[i+1] > A[i+2])
            bval = A[i] + A[i+1] + A[i+2];
    }
    return bval;
}
