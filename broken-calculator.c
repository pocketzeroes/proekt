typedef long long ll;
ll min(ll a, ll b){return a<b?a:b;}

int brokenCalc(int X, int Y){
    ll ret = LLONG_MAX;
    for(int d = 0; d <= 30; d++){
        ll t = ((ll)X<<d)-Y;
        if(t < 0)
            continue;
        ll num = d;
        for(int e = 0; e < d; e++){
            num += t&1;
            t >>= 1;
        }
        num += t;
        ret = min(ret, num);
    }
    return(int)ret;
}
