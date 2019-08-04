int longestDecomposition(char*text){
    int n = strlen(text),i,j,k,l,r;
    int*f = calloc((n>>1)+1, sizeof(int));
    for(i=n>>1;~i;i--){
        l=i;
        r=n-i;
        f[i]=l!=r;
        for(j=1;i+j<=n>>1;j++){
            for(k=0;k<j;k++)
                if(text[l+k]!=text[r-j+k])
                    break;
            if(k==j)
                f[i] = fmax(f[i],f[i+j]+2);
        }
    }
    return f[0];
}
