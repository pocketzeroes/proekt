int dp[150000];
int n;
int each[10];

void decode(int x) {
    for (int i = n - 1; i >= 0; i--) {
        each[i] = x % 7;
        x /= 7;
    }
}
int encode() {
    int val = 0;
    for (int i = 0; i < n; i++) {
        val = val * 7 + each[i];
    }
    return val;
}
void ck(int*x, int y){
    if(*x == -1 || *x > y){
       *x = y;
    }
}
int shoppingOffers(int* price, int price_size, int**special, int special_size, int *specialColSizes, int*needs, int needsSz){
    n = price_size;
    int m = special_size;
    memset(dp, -1, sizeof(dp));
    memset(each, 0, sizeof(each));
    dp[0] = 0;
    int S = 0;
    for (int i = 0; i < n; i++) {
        S = S * 7 + need[i];
    }
    for (int i = 0; i < S; i++) {
        if (dp[i] == -1) {
            continue;
        }
        decode(i);
        for (int j = 0; j < n; j++) {
            each[j]++;
            if (each[j] <= need[j]) {
                int ne = encode();
                ck(&dp[ne], dp[i] + price[j]);
            }
            each[j]--;
        }
        for (int j = 0; j < m; j++) {
            bool sol = true;
            for (int k = 0; k < n; k++) {
                each[k] += special[j][k];
                if (each[k] > need[k]) {
                    sol = false;
                }
            }
            if (sol) {
                int ne = encode();
                ck(&dp[ne], dp[i] + special[j][n]);
            }
            for (int k = 0; k < n; k++) {
                each[k] -= special[j][k];
            }
        }
    }
    return dp[S];
}






