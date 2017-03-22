inline int min(int a,int b){return a<b?a:b;}
inline int max(int a,int b){return a>b?a:b;}

int getMoneyAmount(int n) {
    int pay[n*2][n*2];
    memset(pay,0,sizeof(pay));
    for (int i = n - 1; i >= 0; --i) {
        for (int j = i + 1; j < n; ++j) {
            pay[i][j] = INT_MAX;
            for (int k = i; k <= j; ++k) {
                pay[i][j] =(size_t) min(pay[i][j], k + 1 + max(pay[i][k>0?k-1:k], pay[k + 1][j]));
            }
        }
    }
    return pay[0][n - 1];
}
