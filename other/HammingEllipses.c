#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

enum{ MIN_Q =   2};
enum{ MAX_Q =  10};
enum{ MAX_N = 100};
enum{ MIN_D =   1};

typedef long long ll;
int gn;

int gcd(int p, int q){
    while (q > 0){
        int t = p % q;
        p = q;
        q = t;
    }
    return p;
}
ll binom(int n, int k){
    ll b = 1;
    for (int i = 1; i <= k; i++){
        int p = i + n - k;
        int q = i;
        int g = gcd(p, q);
        p /= g;
        q /= g;
        b /= q;
        b *= p;
    }
    return b;
}
int hamming_distance(int*f1, int*f2){
    int d = 0;
    for (int i = 0, n = gn; i < n; i++) {
        if (f1[i] != f2[i])
            d++;
    }
    return d;
}
ll solve(int q, int n, int d, int*f1, int*f2){
    int fdist = hamming_distance(f1, f2);
    if (q == 1)
        return (d == 0) ? 1 : 0;
    ll ans = 0;
    for (int k = 0; k <= fdist; k++) {
        if (q == 2 && k > 0)
            continue;
        int u = d - fdist - k;
        if (u < 0 || u % 2 != 0 || u/2 > n - fdist)
            continue;
        int p = u / 2;
        ll a = binom(fdist, k);
        for (int i = 0; i < fdist-k; i++)
            a *= 2;
        for (int i = 0; i < k; i++)
            a *= (q-2);
        ll t = binom(n-fdist, p);
        a *= t;
        for (int i = 0; i < p; i++)
            a *= (q-1);
        ans += a;
    }
    return ans;
}
int main(){
    int q, d, n;
    scanf("%d %d %d", &q, &n, &d);
    gn = n;
    void getf(int*v){
        scanf(" ");
        for(int i=0; i<n; i++){
            int c;
            c = fgetc(stdin);
            c -= '0';
            v[i] = c;
        }
    }
    int f1[n]; getf(f1);
    int f2[n]; getf(f2);
    ll ans = solve(q, n, d, f1, f2);
    printf("%lld\n", ans);
    return 0;
}

