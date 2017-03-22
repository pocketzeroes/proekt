bool isInterleave(char* s1, char* s2, char* s3){
    int s1length=strlen(s1);
    int s2length=strlen(s2);
    int s3length=strlen(s3);
    if(s1length + s2length != s3length ) 
        return false;
    if(s1length < s2length ) 
        return isInterleave(s2, s1, s3);
    bool f[s2length + 1];
    memset(f,1,sizeof(f));
    for(int j = 1; j <= s2length; ++j){
        f[j] = f[j - 1] && s2[j - 1] == s3[j - 1];
    }
    for(int i = 1; i <= s1length; ++i) {
        f[0] = f[0] && s1[i - 1] == s3[i - 1];
        for(int j = 1; j <= s2length; ++j) {
            f[j] = (f[j] && s1[i - 1] == s3[i + j - 1]) || (f[j - 1] && s2[j - 1] == s3[i + j - 1]);
        }
    }
    return f[s2length];
}

