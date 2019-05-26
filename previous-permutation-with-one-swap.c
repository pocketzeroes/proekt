void swap(int*nums, int i, int j) {
   int t   = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}
bool check(int*A, int asz){
    int n = asz;
    for(int i = 0; i < n - 1; i++)
        if(A[i] > A[i + 1])
            return false;
    return true;
}
int*prevPermOpt1(int*pA, int Asz, int*rsz){
   *rsz=Asz;
    int*A=calloc(Asz, sizeof(int));
    for(int i=0; i<Asz; i++)
        A[i] = pA[i];
    if(check(A, Asz))
        return A;
    int n      = Asz, 
        pos    = 0,
        maxval = 0;
    for(int i = 0; i < n - 1; i++)
        if(A[i] > A[i + 1])
            pos = i;
    int swappos = 0;
    for(int i = pos + 1; i < n; i++){
        if(A[i] < A[pos] && A[i] != A[i - 1])
            swappos = i;
        else
            break;
    }
    swap(A, pos, swappos);
    return A;
}
