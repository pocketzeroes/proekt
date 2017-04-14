#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>




typedef struct trip{
    int first;
    int second;
    int third;
}trip;
trip newTrip(int a, int b, int c){
    trip rez;
    rez.first =a;
    rez.second=b;
    rez.third =c;
    return rez;
}


int cmp( trip a, trip b)
{
    int diff;
    diff = a.first  - b.first;  if(diff!=0) return diff;
    diff = a.second - b.second; if(diff!=0) return diff;
    return a.third  - b.third;
}
trip min( trip a, trip b){
    if( cmp(a,b) < 0 )
        return a;
    else 
        return b;
}




typedef long long ll;
typedef long double ld;
enum{ MAXN = 120000};
trip ans;
int a [MAXN];
int dp[MAXN];
int n;

void upd(int a, int b, int c) {
    if (b <= 0)             return;
    if (c < 2 || c > n - 2) return;
    if ( ans.first == -1)   ans = newTrip(a, b, c);
    else                    ans = min(ans, newTrip(a, b, c));
}
int merge(int a, int b) {
    if (a ==  b) return a;
    if (a == -1) return b;
    if (b == -1) return a;
    return 0;
}
void solve() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
        scanf("%d", a + i);
    dp[n - 1] = -1;
    ans = newTrip(-1, -1, -1);
    for (int i = n - 2; i >= 0; --i) {
        if (dp[i + 1] == -1)                   dp[i] = a[i + 1] - a[i];
        else if (dp[i + 1] != a[i + 1] - a[i]) dp[i] = 0;
        else                                   dp[i] = dp[i + 1];
    }
    if (a[1] != a[0]) {
        int d   = a[1] - a[0];
        int len = 2;
        int pr  = a[1];
        int d2  = -1;
        int pr2 = -1;
        for (int i = 2; i < n; ++i) {
            int td2 = merge(d2, dp[i]);
            if (pr2 != -1)            td2 = merge(td2, a[i] - pr2);
            if (td2 != 0)             upd(a[0], d, len);
            if (a[i] == pr + d) {
                pr  += d;
                len += 1;
            }
            else {
                if (pr2 != -1)
                    d2 = merge(d2, a[i] - pr2);
                pr2 = a[i];
            }
        }
        if (d2 != 0)
            upd(a[0], d, len);
    }
    if (a[2] != a[0]) {
        int d   = a[2] - a[0];
        int len = 2;
        int pr  = a[2];
        int d2  = -1;
        int pr2 = a[1];
        for (int i = 3; i < n; ++i) {
            int td2 = merge(d2, dp[i]);
            if (pr2 != -1) td2 = merge(td2, a[i] - pr2);
            if (td2 != 0)  upd(a[0], d, len);
            if (a[i] == pr + d) {
                pr  += d;
                len += 1;
            }
            else {
                if (pr2 != -1)
                    d2 = merge(d2, a[i] - pr2);
                pr2 = a[i];
            }
        }
        if (d2 != 0)
            upd(a[0], d, len);
    }
    if (a[2] != a[1]) {
        int d   = a[2] - a[1];
        int len = 2;
        int pr  = a[2];
        int d2  = -1;
        int pr2 = a[0];
        for (int i = 3; i < n; ++i) {
            int td2 = merge(d2, dp[i]);
            if (pr2 != -1) td2 = merge(td2, a[i] - pr2);
            if (td2 !=  0) upd(a[0], td2, n - len);
            if (a[i] == pr + d) {
                pr  += d;
                len += 1;
            }
            else {
                if (pr2 != -1)
                    d2 = merge(d2, a[i] - pr2);
                pr2 = a[i];
            }
        }
        if (d2 != 0)
            upd(a[0], d2, n - len);
    }
    if( ans.first == -1)
        puts("-1");
    else
        printf("%d %d %d\n",ans.first, ans.second, ans.third);
}
int main() {
    int tt;
    scanf("%d", &tt);
    for (int i = 0; i < tt; ++i)
        solve();
    return 0;
}



















