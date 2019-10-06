typedef long long ll;
const ll MOD = 1e9 + 7;

char*nb[5] = {"01000", "10100", "11011", "00101", "10000"};
ll dp[5], ndp[5];

int countVowelPermutation(int n) {
    for (int i = 0; i < 5; i++)
        dp[i] = 1;
    for (int i = 1; i < n; i++){
        for (int j = 0; j < 5; j++)
            ndp[j] = 0;
        for (int j = 0; j < 5; j++)
            for (int k = 0; k < 5; k++)
                if (nb[j][k] == '1')
                    ndp[k] += dp[j];
        for (int j = 0; j < 5; j++)
            dp[j] = ndp[j] % MOD;
    }
    ll ans = 0;
    for (int i = 0; i < 5; i++)
        ans += dp[i];
    ans %= MOD;
    return ans;
}
