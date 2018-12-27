typedef long long ll;


void amin(ll*x, ll y){
    if(y < *x)
       *x = y;
}
double minAreaFreeRect(int**P, int Psz, int*P0sz){
    int N = Psz;
    bool find = false;
    ll ans = 1LL<<60;
    for(int a=0, a_len=(N); a<a_len; ++a) for(int b=0, b_len=(N); b<b_len; ++b) for(int c=0, c_len=(N); c<c_len; ++c) for(int d=0, d_len=(N); d<d_len; ++d){
        if (a == b || a == c || a == d || b == c || b == d || c == d) continue;
        if (P[a][0] - P[b][0] != P[d][0] - P[c][0]) continue;
        if (P[a][1] - P[b][1] != P[d][1] - P[c][1]) continue;
        ll x1 = P[a][0] - P[b][0];
        ll x2 = P[c][0] - P[b][0];
        ll y1 = P[a][1] - P[b][1];
        ll y2 = P[c][1] - P[b][1];
        if (x1 * x2 + y1 * y2 == 0) {
            ll area = abs(x1 * y2 - x2 * y1);
            if (area > 0) {
                find = true;
                amin(&ans, area);
            }
        }
    }
    if (!find)
        return 0;
    return ans;
}
