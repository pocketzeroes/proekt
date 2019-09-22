typedef long long ll;
ll gcd(ll a, ll b){
    while (b != 0){
        ll t = b;
        b = a % b;
        a = t;
    }
    return a;
}
int nthUglyNumber(int n, int a, int b, int c){
    ll aa = a, bb = b, cc = c, g = gcd(gcd(a, b), c);
    ll ab = aa * bb / gcd(aa, bb), bc = bb * cc / gcd(bb, cc), ac = aa * cc / gcd(aa, cc);
    ll abc = ab / gcd(ab, bc);
    abc *= bc;
    ll nn = n;
    ll x, y, z;
    x = 0; y = 3000000000;
    while (x < y) {
        z = (x + y) / 2;
        ll ct = z / aa + z / bb + z / cc - z / ab - z / ac - z / bc + z / abc;
        if (ct < nn) x = z + 1;
        else y = z;
    }
    return x;
}
