int cmp(const void * a, const void * b){ return ( *(int*)a - *(int*)b );}
int repeatedNTimes(int*A, int Asz){
    int n = Asz;
    qsort(A, Asz, sizeof(int), cmp);
    for(int i=0, j=0; i<n; i=j){
        while(j < n && A[i] == A[j])
            j++;
        if (j - i > 1)
            return A[i];
    }
    return -1;
}
