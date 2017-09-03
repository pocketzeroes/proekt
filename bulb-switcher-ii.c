int min(int a,int b){return a<b?a:b;}

int flip(int num, int bit) {
    return num ^ (1 << bit);
}
int op1(int num, int B) {
    for (int i = 0; i < B; ++i) {
        num = flip(num, i);
    }
    return num;
}
int op2(int num, int B) {
    for (int i = 1; i < B; i += 2) {
        num = flip(num, i);
    }
    return num;
}
int op3(int num, int B) {
    for (int i = 0; i < B; i += 2) {
        num = flip(num, i);
    }
    return num;
}
int op4(int num, int B) {
    for (int i = 0; i < B; i += 3) {
        num = flip(num, i);
    }
    return num;
}
int flipLights(int n, int m){
    int B = min(6, n);
    int T = (1 << B);
    bool dp[T]; memset(dp,0,sizeof(dp));
    dp[0] = true;
    for(int i = 0; i < m; ++i){
        bool next[T]; memset(next, 0, sizeof(next));
        for(int j = 0; j < T; ++j){
            if(dp[j]){
                next[op1(j, B)] = true;
                next[op2(j, B)] = true;
                next[op3(j, B)] = true;
                next[op4(j, B)] = true;
            }
        }
        memcpy(dp, next, sizeof(dp));
    }
    int cnt = 0;
    for(int i=0; i<T; i++)
        if(dp[i])
            ++cnt;
    return cnt;
}











