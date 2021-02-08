int minimumLength(char*s){
    int L = 0;
    int R = strlen(s)-1;
    while(L < R && s[L] == s[R]){
        char c = s[L];
        L++;
        R--;
        while(L <= R && s[L] == c)
          L++;
        while(L <= R && s[R] == c)
          R--;
    }
    if(R < L)
      return 0;
    return R-L+1;
}
