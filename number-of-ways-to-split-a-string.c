enum{M=(int)1e9+7};

int numWays(char*s){
    int a=0, n=strlen(s);
    for(int z=0;s[z];z++){char c=s[z];
        a+=c&1;
    }
    if(a%3)
        return 0;
    if(!a)
        return(long long)(n-1)*(n-2)/2%M;
    long long c1=0, c2=0;
    int t=0;
    for(int i=0; i<n; ++i){
        t+=s[i]&1;
        if(t==a/3)
            ++c1;
        if(t==2*a/3)
            ++c2;
    }
    return c1*c2%M;
}
