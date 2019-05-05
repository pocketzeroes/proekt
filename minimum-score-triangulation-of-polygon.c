int min(int a,int b){return a<b?a:b;}

enum{ MAX = 55          };
enum{ INF =(int) 1e9 + 5};
int*A;
int n;
int dp[MAX][MAX];

int prev(int x){
    return (x + n - 1) % n;
}
int next(int x) {
    return (x + 1) % n;
}
int solve(int start, int end) {
    if (start == end || next(start) == end || prev(start) == end)
        return 0;
#define answer dp[start][end]
    if (answer >= 0)
        return answer;
    answer = INF;
    for (int i = next(start); i != end; i = next(i))
        answer = min(answer, A[start] * A[i] * A[end] + solve(start, i) + solve(i, end));
    return answer;
}
int minScoreTriangulation(int*a, int aSz) {
    A = a;
    n = aSz;
    memset(dp, -1, sizeof(dp));
    int best = INF;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            for (int k = j + 1; k < n; k++)
                best = min(best, A[i] * A[j] * A[k] + solve(i, j) + solve(j, k) + solve(k, i));

    return best;
}
