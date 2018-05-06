int uniqueLetterString(char*s){
    int n = strlen(s);
    int mod = 1000000007;
    long long ret = 0ll;
    for(int i = 0; i < n; i++){
        int l = i-1;
        for(;l >= 0 && s[l] != s[i];l--);
        int r = i+1;
        for(;r < n && s[r] != s[i];r++);
        ret += (long long)(r-i)*(i-l);
    }
    return (int)(ret%mod);
}
