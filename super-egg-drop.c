#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))

enum{ N =(int) 1e4 + 10};
enum{ K =(int) 1e2 + 10};
int dp[K][N];

int superEggDrop(int m, int n) {
    for (int i = 0; i <= n; ++i) 
        dp[1][i] = i;
    for (int i = 2; i <= m; ++i) {
        dp[i][0] = 0;
        for (int j = 1; j <= n; ++j) {
            int best = 1 << 30;
            int low = 1, high = j;
            while (low != high) {
                int mid = (low + high) / 2;
                if (dp[i][j - mid - 1] > dp[i - 1][mid - 1])
                    low = mid + 1;
                else
                    high = mid;
            }
            for (int k = max(1, high - 5); k <= high + 5 && k <= j; ++k)
                best = min(best, max(dp[i][j - k], dp[i - 1][k - 1]));
            dp[i][j] = best + 1;
        }
    }
    return dp[m][n];
}
