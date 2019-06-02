int min(int a,int b){return a<b?a:b;}

char*gcdOfStrings(char*str1, char*str2){
    int N = strlen(str1),
        M = strlen(str2);
    for(int len=min(N, M); len>=1; len--){
        if (N % len == 0 && M % len == 0) {
            bool ok = true;
            for(int i=0, i_len=(N); i<i_len; ++i)
                if (str1[i] != str1[i%len])
                    ok = false;
            for(int i=0, i_len=(M); i<i_len; ++i)
                if (str2[i] != str1[i%len])
                    ok = false;
            if (ok){
                str1[len] = '\0';
                return strdup(str1);
            }
        }
    }
    return strdup("");
}
