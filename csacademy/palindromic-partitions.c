#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

typedef long long ll;
typedef long long llong;
typedef long double ld;
typedef unsigned long long ull;

char s[1000100];
typedef ull hsh;
const hsh P = 23917;

void solve() {
    scanf(" %s", s);
    int n = strlen(s);
    int now = 0;
    int lm = n / 2;
    int ans = 0;
    while (1) {
        hsh h1 = 0;
        hsh h2 = 0;
        int go = -1;
        hsh pw = 1;
        for (int i = 0; now + i < lm; ++i, pw *= P) {
            h1 = h1 * P + s[now + i];
            h2 = h2 + pw * s[n - 1 - now - i];
            if (h1 == h2) {
                go = i;
                break;
            }
        }
        if (go == -1) {
            if (now * 2 == n)
                printf("%d\n", ans);
            else
                printf("%d\n", ans+1);
            return;
        }
        else {
            now += go + 1;
            ans += 2;
        }
    }

}
int main() {
    int tt;
    scanf("%d", &tt);
    for (int i = 0; i < tt; ++i)
        solve();
    return 0;
}






































