#include<stdio.h>

enum{ mod = 1000007};
int c[405][405];

int main(void){
    c[0][0] = 1;
    int i,j;
    for(i = 1; i < 405; i++){
        c[i][0] = c[i][i] = 1;
        for(j = 1; j < i; j++)
            c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % mod;
    }
    int t, cas = 0, n, m, k, ans, s1, s2, s3, s4;
    scanf("%d", &t);
    while(t--){
        scanf("%d %d %d", &n, &m, &k);
        if (n * m < k) 
            ans = 0;
        else{
            s1  = (c[n * m - m][k] + c[n * m - n][k]) << 1;
            s2  = c[n * m - m - m][k] + c[n * m - n - n][k] + (c[n * m - n - m + 1][k] << 2);
            s3  = (c[n * m - n - m - m + 2][k]  + c[n * m - m - n - n + 2][k]) << 1;
            s4  = c[n * m - m - m - n - n + 4][k];
            ans = ((c[n * m][k] - s1 + s2 - s3 + s4) % mod + mod) % mod;
        }
        printf("Case %d: %d\n", ++cas, ans);
    }
    return 0;
}
