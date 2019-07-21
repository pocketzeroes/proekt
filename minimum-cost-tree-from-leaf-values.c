typedef long long ll;
ll min(ll a, ll b){return a<b?a:b;}
ll max(ll a, ll b){return a>b?a:b;}

enum{ N_MAX = 105};
const ll LL_INF = (ll)2e18+5;
int n;
int*leaves;
ll dp[N_MAX][N_MAX];

ll solve(int start, int end){
    if(end - start <= 1)
        return 0;
#define answer dp[start][end]
    if (answer >= 0)
        return answer;
    answer = LL_INF;
    for (int i = start + 1; i < end; i++){
        int left  = 0, 
            right = 0;
        for (int j = start; j < i; j++)
            left = max(left, leaves[j]);
        for (int j = i; j < end; j++)
            right = max(right, leaves[j]);
        answer = min(answer, left * right + solve(start, i) + solve(i, end));
    }
    return answer;
}
int mctFromLeafValues(int*arr, int arrSz){
    leaves = arr;
    n = arrSz;
    memset(dp, -1, sizeof(dp));
    return solve(0, n);
}
