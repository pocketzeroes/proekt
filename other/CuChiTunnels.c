#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
typedef unsigned long long ull;
enum{ maxn = 2000005};
enum{ inf  = 0x3f3f3f3f};
#define mod ((ll)1e9+7)
ll ves[maxn];
int a [maxn];

ll read(){
    ll x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch>'9') {
        if (ch == '-') {
            f = -1;
        }
        ch = getchar();
    }
    while (ch >= '0'&&ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
ll quickpow(ll a, ll b){
    ll ans = 1;
    while (b > 0) {
        if (b % 2)ans = ans * a%mod;
        b = b / 2;
        a = a * a%mod;
    }
    return ans;
}
int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a%b);
}
void revs() {
    for (ll i = 1; i <= 1000000; i++) {
        ves[i] = quickpow(i, mod - 2);
    }
}
int main() {
    int n;
    scanf("%d", &n);
    int i;
    int tot = 0;
    for(i = 1; i <= n; i++){
        scanf("%d", &a[i]);
        tot += a[i];
    }
    int cnt  = 0;
    int flag = 0;
    if(tot % 2 == 0 && tot / 2 == n - 1){
        for (i = n; i >= 1; i--){
            if (i == 1)
                cnt -= a[i];
            else if (a[i] != 1 && i != 1){
                if (cnt < a[i] - 1){
                    flag = 1;
                    break;
                }
                cnt -= a[i] - 2;
            }
            else
                cnt++;
        }
        if(flag == 1 || cnt < 0)
            puts("NO");
        else 
            puts("YES");
    }
    else
        puts("NO");
    return 0;
}
