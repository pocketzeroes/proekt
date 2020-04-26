int maxScore(char*s){
    int c0=0,c1=0,ans=0;
    for(int z=0;s[z];z++){char c=s[z];
        c1+=c=='1';
    }
    int ssize = strlen(s);
    for(int i=0; i+1<ssize; ++i){
        c1-=s[i]=='1';
        c0+=s[i]=='0';
        ans = fmax(ans, c0+c1);
    }
    return ans;
}
