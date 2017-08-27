bool checkPossibility(int*a, int a_size){
    int n = a_size;
    bool A[n]; memset(A,0,sizeof(A));
    bool B[n]; memset(B,0,sizeof(B));
    A[0] = true;
    for(int i = 1; i < n; ++i){
        A[i] = A[i - 1] && (a[i] >= a[i - 1]);
    }
    B[n - 1] = true;
    for (int i = n - 2; i >= 0; --i) {
        B[i] = B[i + 1] && (a[i] <= a[i + 1]);
    }
    for (int i = 0; i < n; ++i) {
        bool cur = true;
        if (i - 1 >= 0) cur &= A[i - 1];
        if (i + 1 < n ) cur &= B[i + 1];
        if (i - 1 >= 0 && i + 1 < n) cur &= (a[i - 1] <= a[i + 1]);
        if (cur) return true;
    }
    return false;
}
