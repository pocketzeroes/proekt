int cmp(const void * a, const void * b){    return ( *(int*)a - *(int*)b ); }
int smallestRangeI(int*A, int Asz, int K){
    qsort(A, Asz, sizeof(int), cmp);
    if(A[Asz-1] - A[0]<=2*K)
        return 0;
    return A[Asz-1] - A[0]-2*K;
}
