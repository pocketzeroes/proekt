int min(int a,int b){return a<b?a:b;}

int solve(int a[],int n){
    int cnt[2] = {0,0};
    for (int i = 0; i < (n); ++i)
        cnt[a[i]]++;
    if(abs(cnt[0]-cnt[1])>1)
        return -1;
    int an=1e9;
    if(cnt[0]>=cnt[1]){
        int v=0;
        for (int i = 0; i < (n); ++i)v+=(a[i]!=i%2);
        an = min(an,v/2);
    }
    if(cnt[1]>=cnt[0]){
        int v=0;
        for (int i = 0; i < (n); ++i)v+=(a[i]!=1-i%2);
        an = min(an,v/2);
    }
    return an;
}
int movesToChessboard(int**board, int boardSz, int*_unused){    
    int col[33],row[33];
    int n = boardSz;
    for (int i = 0; i < (n); ++i)
        col[i]=board[0][i];
    for (int i = 0; i < (n); ++i)
        row[i]=col[0]^board[i][0];
    for (int i = 0; i < (n); ++i)
        for (int j = 0; j < (n); ++j){
            if((row[i]^col[j])!=board[i][j])
                return -1;
        }
    int res1 = solve(col, n);
    int res2 = solve(row, n);
    if(res1==-1||res2==-1)
        return -1;
    return res1+res2;
}
