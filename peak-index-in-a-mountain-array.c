int peakIndexInMountainArray(int*A, int Asz){
    for(int i = 1; i < Asz - 1; i++)
        if(A[i] > A[i-1] && A[i] > A[i+ 1])
            return i;
    return 0;
}
