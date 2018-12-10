int minDeletionSize(char**A, int Asz){
    int n = Asz,
        m = strlen(A[0]),
            ans=0,i,j;
    int a[n]; memset(a, 0, sizeof(a));
    int b[n]; memset(a, 0, sizeof(b));
    for(i=0; i<m; i++){
        for(j=0; j+1<n; j++)
            if(a[j]==a[j+1]&&A[j][i]>A[j+1][i])
                break;
        if(j+1<n){
            ans++;
            continue;
        }
        for(j=1;j<n;j++)
            if(a[j]!=a[j-1]||A[j][i]!=A[j-1][i])
                b[j]=b[j-1]+1;
        else
            b[j]=b[j-1];
        for(j=0;j<n;j++)
            a[j]=b[j];
    }
    return ans;
}
