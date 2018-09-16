typedef long long ll;
int reversei(int x){
    int a[30];
    int cnt = 0;
    while (x != 0) {
        a[cnt++] = x % 10;
        x /= 10;
    }
    int ret = 0;
    for (int i = 0; i < cnt; i++)
        ret = ret * 10 + a[i];
    return ret;
}
ll reverse(ll x){
    int a[30];
    int cnt = 0;
    while (x != 0) {
        a[cnt++] = x % 10;
        x /= 10;
    }
    ll ret = 0;
    for (int i = 0; i < cnt; i++)
        ret = ret * 10 + a[i];
    return ret;
}
int superpalindromesInRange(char*_L, char*_R){
    ll L, R;
    sscanf(_L, "%lld", &L);
    sscanf(_R, "%lld", &R);
    int ans = 0;
    for(int len_left=1; len_left<=5; len_left++){
        int lower = 1;
        for (int i = 1; i < len_left; i++)
            lower *= 10;
        int upper = lower * 10 - 1;
        for (int left = lower; left <= upper; left++) {
            int right = reversei(left);
            int x = left * (upper + 1) + right;
            ll tmp = 1LL * x * x;
            if (tmp >= L && tmp <= R && reverse(tmp) == tmp) 
                ++ans;
            x = left / 10 * (upper + 1) + right;
            tmp = 1LL * x * x;
            if (tmp >= L && tmp <= R && reverse(tmp) == tmp) 
                ++ans;
        }
    }
    return ans;
}
