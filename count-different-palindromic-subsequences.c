typedef long long ll;
enum{ mod = 1000000007LL};
char s [1010];
int nxt[1010][26];
int lst[1010][26];
ll  dp [1010][1010];

ll f(int l, int r){
#define ret dp[l][r]
  if (ret >= 0)
    return ret;
  if (l > r) return ret = 1;
  ret = 1;
  for (int i = 0; i < 26; ++i){
    int a = nxt[l][i];
    int b = lst[r][i];
    if (a < b) ret += f(a + 1, b - 1);
    if (a <= r) ret += 1;
  }
  ret %= mod;
  return ret;
  #undef ret
}
int countPalindromicSubsequences(char*S){
  strcpy(s + 1, S);
  int n = strlen(s + 1);
  for (int i = 0; i < 26; ++i) nxt[n + 1][i] = n + 1;
  for (int i = n; i >= 1; --i) {
    for (int j = 0; j < 26; ++j) nxt[i][j] = nxt[i + 1][j];
    nxt[i][s[i] - 'a'] = i;
  }
  for (int i = 0; i < 26; ++i) lst[0][i] = 0;
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j < 26; ++j) lst[i][j] = lst[i - 1][j];
    lst[i][s[i] - 'a'] = i;
  }
  memset(dp, -1, sizeof dp);
  ll ans = f(1, n);
  ans = ans == 0 ? mod - 1 : ans - 1;
  return ans;
}
