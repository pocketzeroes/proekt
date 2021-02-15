int countHomogenous(char*s){
    int ans = 0;
    enum{MOD =(int)1e9+7};
    int s_size=strlen(s);
    for(int i=0; i<s_size;){
        int j = i + 1;
        while(j < s_size && s[i] == s[j]){
            ++j;
        }
        int len = j - i;
        ans += (1LL * len * (len + 1) / 2) % MOD;
        ans %= MOD;
        i = j;
    }
    return ans;
}
