int*sortArrayByParity(int*A, int Asz, int*rsz){
    int n = Asz;
    int*ans = calloc(n, sizeof(int));
    int ansSz = 0;
    for(int i=0; i<n; i++)if(A[i]%2 == 0) ans[ansSz++] = A[i];
    for(int i=0; i<n; i++)if(A[i]%2)      ans[ansSz++] = A[i];
   *rsz = n;
    return ans;
}
