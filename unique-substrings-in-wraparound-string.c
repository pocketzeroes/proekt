int findSubstringInWraproundString(char* p) {
    int letters[26]={0};
    int res = 0, len = 0;
    for (int i = 0; i < strlen(p); i++) {
        int cur = p[i] - 'a';
        if (i > 0 && p[i - 1] != (cur + 26 - 1) % 26 + 'a') 
            len = 0;
        if (++len > letters[cur]) {
            res += len - letters[cur];
            letters[cur] = len;
        }
    }
    return res;
}

