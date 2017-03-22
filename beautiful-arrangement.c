void swap(int*nums, int i, int j) {
   int t   = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}
int counts(int n,int*vs) {
    if (n <= 0) return 1;
    int ans = 0;
    for (int i=0; i<n; ++i) {
        if (vs[i]%n==0 || n%vs[i]==0) {
            swap(vs,i, n-1);
            ans += counts(n-1, vs);
            swap(vs,i, n-1);
        }
    }
    return ans;
}
int countArrangement(int N) {
    int vs[N];
    
    for (int i=0; i<N; ++i) 
        vs[i]=(i+1);
    return counts(N, vs);
}
