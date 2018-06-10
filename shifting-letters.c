char*shiftingLetters(char*S, int*a, int aSz){
    int n = aSz;
    for (int i = n - 2; i >= 0; --i) {
        a[i] += a[i + 1];
        a[i] %= 26;
    }
    for (int i = 0; i < n; ++i) {
        int k = S[i] - 'a';
        k = (k + a[i]) % 26;
        S[i] = (char)('a' + k);
    }
    return S;
}
