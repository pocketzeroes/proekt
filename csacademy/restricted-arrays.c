#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
inline ll max(ll a, ll b){return a>b?a:b;}
enum{ maxN = 100011};
#define mod 1000000007LL

int n, k, i;
int a[maxN];
int last[maxN], act, need;
ll ans;

void solve() {
    int i, rm;
    memset(last, 0, sizeof(last));
    ans = 1;
    act = 0;
    for (i = 0; i < n; i++) {
        rm = (i - k + 1);
        if (rm > 0) {
            if (last[a[rm]] == rm) 
                act--;
        }
        if (last[a[i + 1]] < max(1, i - k + 2)) {
            ans = (ans * (need - act)) % mod;
            act++;
        }
        last[a[i + 1]] = i + 1;
        need = max(need, act);
    }
}
int main() {
    scanf("%d%d", &n, &k);
    for (i = 1; i <= n; i++) 
        scanf("%d", &a[i]);
    solve(); 
    solve(); 
    printf("%lld", ans);
    return 0;
}
