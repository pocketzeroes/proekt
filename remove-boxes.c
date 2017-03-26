inline int min(int a,int b){return a<b?a:b;}
inline int max(int a,int b){return a>b?a:b;}

int dfs(int*boxes, int memo[100][100][100], int l,int r,int k){
    if (l>r) return 0;
    if (memo[l][r][k]!=0) return memo[l][r][k];
    memo[l][r][k] = dfs(boxes,memo,l,r-1,0) + (k+1)*(k+1);
    for (int i=l; i<r; i++){
        if (boxes[i]==boxes[r]){
            memo[l][r][k] = max(memo[l][r][k], dfs(boxes,memo,l,i,k+1) + dfs(boxes,memo,i+1,r-1,0));
        }
    }
    return memo[l][r][k];
}
int removeBoxes(int* boxes, int boxesSize) {
    int n=boxesSize;
    int memo[100][100][100] = {0};
    return dfs(boxes,memo,0,n-1,0);
}
