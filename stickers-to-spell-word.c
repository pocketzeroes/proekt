enum{ MOD  =(int)1e9+7 };
enum{ SIZE =(int)1<<15 };
int dp[SIZE];

void update(int*x, int v){
    if(*x==-1||*x>v)
       *x = v;
}
int minStickers(char**stickers, int stickersSz, char*target){
    memset(dp, -1, sizeof(dp));
    dp[0] = 0;
    int n = strlen(target);
    int N = 1<<n;
    for(int i = 0; i < N; ++i){
        if(dp[i]==-1)
            continue;
        for (int j = 0; j < stickersSz; ++j){
            int now = i;
            char*stik = stickers[j];
            for(int k = 0; stik[k]; ++k){
                for(int r = 0; r < n; ++r){
                    if((now>>r)&1)
                        continue;
                    if(target[r] == stickers[j][k]){
                        now |= 1<<r;
                        break;
                    }
                }
            }
            update(&dp[now], dp[i]+1);
        }
    }
    return dp[N-1];
}
