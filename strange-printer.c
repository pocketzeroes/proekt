int min(int a,int b){return a<b?a:b;}

int n;
int v[100];
int dp[100][100][100];

int f(int a, int b, int k) {
    if (b < a)
        return 0;
#define res dp[a][b][k]
    if (res >= 0)
        return res;
    res = f(a, b - 1, 0) + 1;
    for (int i = a; i < b; i++)
        if (v[i] == v[b])
            res = min(res, f(a, i, k + 1) + f(i + 1, b - 1, 0));
    return res;
}
int strangePrinter(char*s){
    n = strlen(s);
    for (int i = 0; i < n; i++)
        v[i] = s[i];
    memset(dp, -1, sizeof dp);
    return f(0, n - 1, 0);
}
