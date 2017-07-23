int countSubstrings(char*s){
    int ans = 0;
    int n = strlen(s);
    if(n == 0) 
        return 0;
    for(int i = 0; i < n; i++){
        int l = i, r = i;
        while(l >= 0 && r < n && s[l] == s[r]){
            l--, r++;
        }
        l++, r--;
        ans += r - i + 1;
    }
    for(int i = 0; i + 1 < n; i++){
        if(s[i] != s[i + 1]) 
            continue;
        int l = i, r = i + 1;
        while(l >= 0 && r < n && s[l] == s[r]){
            l--, r++;
        }
        l++, r--;
        ans += r - (i + 1) + 1;
    }
    return ans;
}
