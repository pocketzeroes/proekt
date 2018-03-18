int min(int a,int b){return a<b?a:b;}

int minSwap(int* A, int Asize, int* B, int BSize){
    int f[1005][2], n=Asize, i;
    memset(f, 127, sizeof(f));
    f[0][0]=0;
    f[0][1]=1;
    for(i=1;i<n;i++){
        if(A[i]>A[i-1]&&B[i]>B[i-1])f[i][0]=min(f[i][0],f[i-1][0]);
        if(B[i]>A[i-1]&&A[i]>B[i-1])f[i][1]=min(f[i][1],f[i-1][0]+1);
        if(A[i]>B[i-1]&&B[i]>A[i-1])f[i][0]=min(f[i][0],f[i-1][1]);
        if(B[i]>B[i-1]&&A[i]>A[i-1])f[i][1]=min(f[i][1],f[i-1][1]+1);
    }
    return min(f[n-1][0],f[n-1][1]);
}
