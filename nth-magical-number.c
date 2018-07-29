typedef long long ll;
int gcd(int a, int b){
    while (b > 0){
        int c = a;
        a = b;
        b = c % b;
    }
    return a;
}
int nthMagicalNumber(int K, int A, int B){
    ll low = 0, high = 2000000000000000000ll;
    int G = A*B/gcd(A, B);
    while(high - low > 1){
        ll h = high+low>>1;
        ll num = h/A+h/B-h/G;
        if(num >= K)
            high = h;
        else
            low = h;
    }
    return (int)(high%1000000007);
}
