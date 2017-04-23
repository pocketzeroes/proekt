int max(int a,int b){return a>b?a:b;}

int longestLine(int** M, int Mlength, int M0length){
    int n = Mlength;
    if(n == 0){
        return 0;
    }
    int m = M0length;
    if(m == 0)return 0;
    int ans = 0;
    for(int i = 0;i < n;i++){
        for(int j = 0;j < m;j++){
            if(M[i][j] == 0)continue;
            for(int k = -1;k <= 1;k++){
                for(int l = -1;l <= 1;l++){
                    if(k == 0 && l == 0)continue;
                    int len = 0;
                    for(int r = i, c = j;r >= 0 && r < n && c >= 0 && c < m && M[r][c] == 1;r+=k,c+=l){
                        len++;
                    }
                    ans = max(ans, len);
                }
            }
        }
    }
    return ans;
}
