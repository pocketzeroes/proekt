int numDistinct(char*S,char*T){
    int Tsize=strlen(T);
    int Ssize=strlen(S);
    int f[ Tsize + 1 ];
    memset (f, 0, sizeof(f));
    f[0] = 1;
    for (int i = 1; i <= Ssize; ++i) {
        for (int j = Tsize; j > 0; --j) {
            f[j] += (S[i - 1] == T[j - 1]) ? f[j - 1] : 0;
        }
    }
    return f[ Tsize ];
}
