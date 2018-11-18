int minDeletionSize(char**A, int Asz){
    int n = Asz, m=strlen(A[0]), i, j, ans=0;
    for(i=0; i<m; i++){
        for(j=0; j+1<n; j++)
            if(A[j][i]>A[j+1][i])
                break;
        if(j+1<n)
            ans++;
    }
    return ans;
}
