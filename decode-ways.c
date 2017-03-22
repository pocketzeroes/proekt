int numDecodings(char* s){
    if(strlen(s)==0)return 0;
    int prev = 0;
    int cur = 1; 
    for (int i = 0; s[i]; ++i) {
        if (s[i] == '0')
            cur = 0; 
        if (i == 0 || !(s[i - 1] == '1' || (s[i - 1] == '2' && s[i] <= '6'))) 
            prev = 0; 
        int tmp = cur;
        cur    += prev; 
        prev    = tmp;
    }
    return cur;
}
