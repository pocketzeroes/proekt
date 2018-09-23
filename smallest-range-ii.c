int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}
int cmp(const void * a, const void * b){    return ( *(int*)a - *(int*)b ); }
int smallestRangeII(int*A, int Asz, int K){
    qsort(A, Asz, sizeof(int), cmp);
    int n=Asz, i, ans = A[Asz-1] - A[0];
    for(i=0; i+1<n; i++)
        ans = min(ans, max(A[i]+K, A[n-1]-K) - min(A[0]+K, A[i+1]-K));
    return ans;
}
