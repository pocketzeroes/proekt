bool b[10005];
int*ans;

int*getNoZeroIntegers(int n, int*rsz){
    memset(b, 0, sizeof(b));
    int i;
    for(i=1; i<10; i++)
        b[i]=1;
    for(;i<=n; i++)
        b[i]=b[i/10]&&i%10;
    for(i=1; i<n; i++)
        if(b[i]&&b[n-i])
            break;
    ans = calloc(2, sizeof(int));
    ans[0]= i;
    ans[1]= n-i;
   *rsz=2;
    return ans;
}
