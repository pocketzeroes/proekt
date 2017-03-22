int countSegments(char*s) {
    int slen=strlen(s);
    int result = (int)(slen>0 && s[slen-1] != ' ');
    for (int i = 1; i < slen; ++i) {
        if (s[i] == ' ' && s[i - 1] != ' ') {
            ++result;
        }
    }
    return result;
}
