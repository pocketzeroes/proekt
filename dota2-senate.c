char* predictPartyVictory(char*s){
    int n = strlen(s);
    bool f[n];
    memset(f, 0, sizeof(f));
    int cnt[2] = {0}; 
    int q  [2] = {0};
    for(int i=0;s[i];i++){ char c = s[i]; 
      cnt[c == 'R']++;
    }
    for (;;) {
        if (cnt[0] == 0) return "Radiant";
        if (cnt[1] == 0) return "Dire";
        for (int i = 0; i < n; ++i) {
            if (f[i]) continue;
            int idx = s[i] == 'R';
            if (q[idx]) {
                q[idx]--;
                cnt[idx]--;
                f[i] = true;
                continue;
            } 
            else {
                q[idx ^ 1]++;
            }
        }
    }
}
