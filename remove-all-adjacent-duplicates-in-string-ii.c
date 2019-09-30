int  a  [100005],t;
char c  [100005];
char ans[100005];
int  ansSz;
char*removeDuplicates(char*s, int k){
    t=0;
    for(int z=0;s[z];z++){char i=s[z];
        if(i==c[t]){
            a[t]++;
            if(a[t]==k)
                t--;
        }
        else{
            c[++t]=i;
            a[t]=1;
        }
    }
    memset(ans,0,sizeof(ans));
    ansSz=0;
    for(int i=1;i<=t;i++)
        for(int j=0;j<a[i];j++)
            ans[ansSz++] = c[i];
    return strdup(ans);
}
