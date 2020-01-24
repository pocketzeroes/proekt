#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
enum{ N = 105};
int T, pos, sum, cnt[N];
ll n, c[N][N], ans, res;

static inline int read(){
    int x = 0, w = 1; char c = getchar();
    while(c < '0' || c > '9') { if(c == '-') w = -1; c = getchar(); }
    while(c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * w;
}
static inline ll readll(){
    ll x = 0, w = 1; char c = getchar();
    while(c < '0' || c > '9') { if(c == '-') w = -1; c = getchar(); }
    while(c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * w;
}

int main(){
    T = read();
    for(int i = 0; i <= 100; i++)
        for(int j = 0; j <= i; j++)
            c[i][j] = (!j ? 1 : c[i - 1][j] + c[i - 1][j - 1]);
    while(T--){
        memset(cnt, 0, sizeof(cnt));
        pos = 1, sum = 0, ans = res = 1;
        n = readll();
        while(n){
            pos++;
            cnt[n % pos]++;
            n /= pos;
        }
        for(int i = pos; i; i--)
            if(cnt[i]){
                ans = ans * c[pos - i - sum][cnt[i]];
                sum += cnt[i];
            }
        sum = 0;
        for(int i = pos; i; i--)
            if(cnt[i]){
                if(pos - 1 - i - sum >= 0)
                    res = res * c[pos - 1 - i - sum][cnt[i]];
                else res = 0;
                sum += cnt[i];
            }
        printf("%lld\n", ans - res - 1);
    }
    return 0;
}
