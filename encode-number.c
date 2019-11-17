char*encode(int n){
    if(n == 0)
        return strdup("");
    int k = 1;
    while(n > (1LL << k)){
        n -= 1LL << k;
        ++k;
    }
    n -= 1;
    char ret[k+1];
    for(int i=k-1; i>=0; i--){
        ret[i]=(char)('0'+n%2);
        n>>=1;
    }
    ret[k]='\0';
    return strdup(ret);
}
