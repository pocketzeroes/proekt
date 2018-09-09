char*itoa(int a){
  char*ptr=NULL;
  asprintf(&ptr, "%d", a);
  return ptr;
}
typedef long long ll;
int atMostNGivenDigitSet(char**D, int Dsz, int N){
    int mask = 0;
    for(int i=0; i<Dsz; i++){char*s = D[i];
        mask ^= 1<<s[0]-'0';
    }
    char*s = itoa(N+1);
    ll dp = 0;
    int e = 1;
    for(int i=0; s[i]; i++){
        dp *= __builtin_popcount(mask);
        for(int j=1; j<s[i]-'0'; j++){
            if(mask<<~j<0)
                dp+=e;
        }
        if(i > 0)
            dp += __builtin_popcount(mask);
        if(mask<<~(s[i]-'0')>=0)
            e = 0;
    }
    return (int)dp;
}
