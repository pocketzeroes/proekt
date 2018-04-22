int cmp (const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}

static int dp[1005];
enum{ MOD = 1000000007};
int numFactoredBinaryTrees(int*A, int Asz){
    qsort(A, Asz, sizeof(int), cmp);
    int n = Asz;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int tmp = 1;
        int k = i - 1;
        for (int j = 0; j < i; j++) {
            while (k > 0 && 1LL * A[j] * A[k] > A[i])
                --k;
            if (k < j) 
                break;
            if (1LL * A[j] * A[k] == A[i]) {
                if (j != k) {
                    tmp = (tmp + 2LL * dp[j] * dp[k]) % MOD;
                }
                else {
                    tmp = (tmp + 1LL * dp[j] * dp[k]) % MOD;
                }
            }
        }
        dp[i] = tmp;
        ans = (ans + tmp) % MOD;
    }
    return ans;
}
