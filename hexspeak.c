typedef long long ll;
char buff[1000];
char*toHexspeak(char*num){
    memset(buff, 0, sizeof(buff));
    char ch[] = { 'O','I','.','.','.','.','.','.',',',',','A','B','C','D','E','F' };
    bool valid = true;
    int ans = 999;
    char*endptr;
    ll n = strtoll(num, &endptr, 10);
    if(n == 0)
        return strdup("O");
    else{
        while(n>0){
            buff[--ans] = ch[n%16];
            if(ch[n % 16] == '.')
                valid = false;
            n /= 16;
        }
        if(!valid)
            return strdup("ERROR");
        return strdup(buff+ans);
    }
}
