bool checkInclusion(char*t, char*s){
    int m = strlen(t), n = strlen(s);
    if (m > n) return false;
    int cnt[26];memset(cnt,0,sizeof(cnt));
    for (int i = 0; i < m; ++i) {
        cnt[t[i] - 'a']++;
    }
    int cur[26];memset(cur,0,sizeof(cur));
    for (int i = 0; i < m; ++i) {
        cur[s[i] -  'a']++;
    }
    bool eq=true;
    for(int i=0;i<26;i++)
      if(cur[i] != cnt[i]){
        eq=false;
        break;
      }
    if(eq)return true;
    for (int k = 1; k + m <= n; ++k) {
        cur[s[k - 1] - 'a']--;
        cur[s[k + m - 1] - 'a']++;
        bool eq=true;
        for(int i=0;i<26;i++)
          if(cur[i] != cnt[i]){
            eq=false;
            break;
          }
        if(eq)return true;
    }
    return false;
}
