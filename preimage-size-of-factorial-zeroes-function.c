typedef long long ll;
ll count(int n){
    ll low = -1, high = 5000000000LL;
    while(high - low > 1){
        ll h = high+low>>1;
        ll s = 0;
        for(ll k = h/5;k > 0;k /= 5)
            s += k;
        if(s <= n)
            low = h;
        else
            high = h;
    }
    return low+1;
}
int preimageSizeFZF(int K){
    return (int)(count(K) - count(K-1));
}
