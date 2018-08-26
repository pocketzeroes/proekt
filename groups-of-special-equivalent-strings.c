enum{ N =(int)1e3 + 10};
int f[N];

int find(int x) {
    if (f[x] != f[f[x]]) 
        f[x] = find(f[x]);
    return f[x];
}
bool same(char*s, char*t){
    int m = strlen(s);
    int cnt[26] = {0};
    for(int i=0; i<m; i+=2){
        cnt[s[i] - 'a']++;
        cnt[t[i] - 'a']--;
    }
    for(int k=0; k<26; ++k){
        if(cnt[k]) 
            return false;
    }
    for(int i=1; i<m; i+=2){
        cnt[s[i] - 'a']++;
        cnt[t[i] - 'a']--;
    }
    for(int k=0; k<26; ++k){
        if(cnt[k]) 
            return false;
    }
    return true;
}
int numSpecialEquivGroups(char**A, int Asz){
    int n = Asz;
    for (int i = 0; i < n; ++i) 
        f[i] = i;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (same(A[i], A[j])) {
                int ri = find(i), 
                    rj = find(j);
                if (ri != rj)
                    f[rj] = ri;
            }
        }
    }
    int ret = 0;
    for (int i = 0; i < n; ++i)
        if (find(i) == i) 
            ++ret;
    return ret;
}
