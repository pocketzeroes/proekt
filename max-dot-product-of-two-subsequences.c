#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
int f[510][510];

int maxDotProduct(int*a,int aSz, int*b, int bSz){
    clr(f);
    int n = aSz,
        m = bSz;
    for(int i=0; i<n; ++i)
        for(int j=0; j<m; ++j){
            f[i][j] = a[i] * b[j];
        }
    for(int i=0; i<n; ++i)
        for(int j=0; j<m; ++j){
            if(i > 0) f[i][j] = fmax(f[i][j], f[i - 1][j]);
            if(j > 0) f[i][j] = fmax(f[i][j], f[i][j - 1]);
            if(i > 0 && j > 0){
                f[i][j] = fmax(f[i][j], f[i - 1][j - 1] + fmax(0, a[i] * b[j]));
            }
        }
    return f[n - 1][m - 1];
}
