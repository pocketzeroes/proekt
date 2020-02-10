int o[256],f[9][256],a[9];
int maxStudents(char**seats, int seatsSz, int*seats0sz){
    int n=seatsSz,m=seats0sz[0],i,j,k,ans=0;
    for(i=1;i<256;i++)o[i]=o[i>>1]+(i&1);
    memset(f,128,sizeof(f));
    memset(a,0,sizeof(a));
    for(i=0;i<n;i++)for(j=0;j<m;j++)if(seats[i][j]=='#')a[i]|=1<<j;
    for(i=f[0][0]=0;i<n;i++)for(j=0;j<1<<m;j++)if(!(j&a[i])&&!(j&j>>1)&&!(j&j<<1))for(k=0;k<1<<m;k++)if(!(j&k>>1)&&!(j&k<<1))f[i+1][j]=fmax(f[i+1][j],f[i][k]+o[j]);
    for(i=0;i<1<<m;i++)ans=fmax(ans,f[n][i]);
    return ans;
}
