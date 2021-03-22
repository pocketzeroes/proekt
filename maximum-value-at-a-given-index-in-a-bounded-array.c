typedef long long ll;
int maxValue(int n, int b, int s){
    int lo=1,hi=(int)1e9;
    ll calc(int len, int x){
        ll ret=0;
        if(len <= x) {
            ll lo = x - len + 1;
            return(lo + x) * len / 2;
        }
        ll lo = 1;
        ret = 1ll * (1 + x) * x / 2;
        len -= x;
        ret += len;
        return ret;
    };
    while(lo<hi){
        int mid=(lo+hi+1)/2;
        ll tot=calc(n-b,mid)+calc(b+1,mid)-mid;
        if(tot>s) hi=mid-1;
        else lo=mid;
    }
    return lo;
}
