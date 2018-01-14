int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}
void fill(int*arr,int sz, int val){
  for(int i=0;i<sz;i++)
    arr[i]=val;
}
int**mat2d(int n){
    int**matrix = calloc(n, sizeof(int*));
    for(int i=0;i<n;i++){
        matrix[i] = calloc(n, sizeof(int));
    }
    return matrix;
}

int orderOfLargestPlusSign(int n, int**mines, int minesSz, int*mines0szs){
    int**matrix = calloc(n,sizeof(int*));
    for(int i=0;i<n;i++){
        matrix[i] = malloc(n*sizeof(int));
        fill(matrix[i], n, 1);
    }
    for(int i=0;i<minesSz;i++){int*zero = mines[i];
        matrix[zero[0]][zero[1]] = 0;
    }
    int**lf=mat2d(n);
    int**rt=mat2d(n);
    int**up=mat2d(n);
    int**dn=mat2d(n);
    for (int i=0; i<n; ++i)
        for (int j=0; j<n; ++j)
            if (matrix[i][j]==1) {
                lf[i][j] = j==0 ? 1 : lf[i][j-1]+1;
                up[i][j] = i==0 ? 1 : up[i-1][j]+1;
            }
    int ans = 0;
    for (int i=n-1; i>=0; --i)
        for (int j=n-1; j>=0; --j)
            if (matrix[i][j]==1) {
                rt[i][j] = j==n-1 ? 1 : rt[i][j+1]+1;
                dn[i][j] = i==n-1 ? 1 : dn[i+1][j]+1;
                ans = max(ans, min(min(lf[i][j], rt[i][j]),min(up[i][j], dn[i][j])));
            }

    for(int i=0;i<n;i++){ free(matrix[i]); } free(matrix);
    for(int i=0;i<n;i++){ free(lf    [i]); } free(lf);
    for(int i=0;i<n;i++){ free(rt    [i]); } free(rt);
    for(int i=0;i<n;i++){ free(up    [i]); } free(up);
    for(int i=0;i<n;i++){ free(dn    [i]); } free(dn);

    return ans;
}
