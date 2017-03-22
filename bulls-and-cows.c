inline int min(int a,int b){return a<b?a:b;}
inline int max(int a,int b){return a>b?a:b;}

char*getHint(char*secret, char*guess){
    int secLen=strlen(secret);
    int gesLen=strlen(guess );
    int lookup[128]={0};
    int A = 0, B = 0;
    for(int i=0;secret[i];i++){
        char s=secret[i];
        ++lookup[s];
    }
    for(int i=0;guess[i];i++){
        char g=guess[i];
        if (lookup[g]){
            --lookup[g];
            ++B;
        }
    }
    int n = min(secLen, gesLen);
    for (int i = 0; i < n; ++i) 
        if (secret[i] == guess[i]) 
            ++A, --B;
    char*rez;
    asprintf(&rez,"%dA%dB", A, B);
    return rez;
}
