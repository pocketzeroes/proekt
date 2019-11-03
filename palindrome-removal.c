int f[105][105];
int minimumMoves(int*arr, int arrSz){
    memset(f,127,sizeof(f));
    int n=arrSz,i,j,k,l;
    for(i=0;i<n;i++)f[i][i]=1;
    for(l=1;l<n;l++)for(i=0;i+l<n;i++)
    {
        j=i+l;
        for(k=i;k<j;k++)f[i][j]=fmin(f[i][j],f[i][k]+f[k+1][j]);
        if(arr[i]==arr[j])if(l==1)f[i][j]=1;
        else f[i][j]=fmin(f[i][j],f[i+1][j-1]);
    }
    return f[0][n-1];
}
