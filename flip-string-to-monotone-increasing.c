int min(int a,int b){return a<b?a:b;}
enum{ INF = (int)1E9};
int cnt[20005];
int minFlipsMonoIncr(char*S){
    int n = strlen(S);
    memset(cnt, 0, sizeof(cnt));
    for(int i=(1); i<(n+1); i++) {
      cnt[i] = S[i-1] == '1';
      cnt[i] += cnt[i-1];
    }
    int ans = INF;
    for(int i=(0); i<(n+1); i++) {
      ans = min(ans, n - i - (cnt[n] - cnt[i]) + cnt[i]);
    }
    return ans;
}
