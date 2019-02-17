typedef long long ll;

int cmp(const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}
bool is_perfect_square(int x) {
    int s = sqrt(x + 0.5);
    return s * s == x;
}
int numSquarefulPerms(int*A, int Asz){
    int n = Asz;
    ll**dp=calloc(1<<n, sizeof(ll*));
    for(int i=0;i < (1<<n);i++){
        dp[i]=calloc(n,sizeof(ll));
    }
    for(int i=0; i<n; i++)
        dp[1 << i][i] = 1;
    for(int mask = 0; mask < 1 << n; mask++)
        for(int end = 0; end < n; end++)
            if(dp[mask][end] != 0)
                for(int next = 0; next < n; next++)
                    if((mask & 1 << next) == 0 && is_perfect_square(A[end] + A[next]))
                        dp[mask | 1 << next][next] += dp[mask][end];
    ll total = 0;
    for(int i = 0; i < n; i++)
        total += dp[(1 << n) - 1][i];
    qsort(A, Asz, sizeof(int), cmp);
    for(int i = 0, j = 0; i < n; i = j) {
        while(j < n && A[i] == A[j])
            j++;
        for(int k = 1; k <= j - i; k++)
            total /= k;
    }
    return total;
}
