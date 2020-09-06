#define FOR(i, begin, end) for(int i=(begin),i##_end_=(end);i<i##_end_;i++)
#define REP(i, n) FOR(i,0,n)

char*modifyString(char*s){
    int N = strlen(s);
    REP(i, N) if (s[i] == '?')
    {
        s[i] = 'a';
        if (i && s[i - 1] == s[i]) s[i]++;
        if (i + 1 < N && s[i] == s[i + 1]) s[i]++;
        if (i && s[i - 1] == s[i]) s[i]++;
        if (i + 1 < N && s[i] == s[i + 1]) s[i]++;
    }
    return s;
}
