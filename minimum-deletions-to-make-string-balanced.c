int minimumDeletions(char*s){
    int ssize=strlen(s);
    int pre[100005];
    pre[0]=0;
    for(int i=0; s[i]; i++){
        pre[i+1]=pre[i];
        if(s[i]=='b')
          pre[i+1]++;
    }
    int suf[100005];
    suf[ssize]=0;
    for(int i = ssize-1;i>=0;i--){
        suf[i]=suf[i+1];
        if(s[i]=='a')suf[i]++;
    }
    int ans=(int)1e9;
    for(int i=0;i<=ssize;i++)ans=fmin(ans,pre[i]+suf[i]);
    return ans;
}
