#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
ll min(ll a, ll b){return a<b?a:b;}
ll max(ll a, ll b){return a>b?a:b;}

char buff[100000];
int main(){
    ll mx = 0;
    ll n, k;
    scanf("%lld %lld", &n, &k);
    char*s;
    scanf("%s", &buff);
    s = strdup(buff);
    ll l = -1, q = -1;
    int ssize = strlen(s);
    for (int i = 0; i <= (int)(ssize) - 1; ++i) {
        if (s[i] == '1') {
            mx = max(mx, i - l - 1);
            l = i;
            if (l != -1 && q == -1)
                q = i;
        }
    }
    mx = max(mx, (int)(ssize) - l - 1);
    if (l == -1)
        return printf("%lld", (int)(ssize) * 1ll * k)*0;
    if (k == 1)
        printf("%lld", mx);
    else
        printf("%lld", max(mx, (int)(ssize) - l - 1 + q));
 return 0;
}
