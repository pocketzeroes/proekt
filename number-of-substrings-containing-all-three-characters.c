#define dfill(arr, sz1, sz2, val)do{     \
  for(int i=0; i<sz1; i++)               \
    for(int j=0; j<sz2; j++)             \
      arr[i][j] = val;                   \
}while(0)
int numberOfSubstrings(char*s){
    int n = strlen(s);
    int dp[3][n+1]; dfill(dp, 3, n+1, -1);
    for(int i = n - 1; i >= 0; i--){
        for (int j = 0; j < 3; j++)
            dp[j][i] = dp[j][i + 1];
        dp[s[i] - 'a'][i] = i;
    }
    long long ans = 0;
    for (int i = 0; i < n; i++){
        bool ok = true;
        for (int j = 0; j < 3; j++){
            if (dp[j][i] == -1) 
                ok = false;
        }
        if (ok){
            int mx = -1;
            for (int j = 0; j < 3; j++) 
                mx = fmax(mx, dp[j][i]);
            ans += n - mx;
        }
    }
    return ans;
}
