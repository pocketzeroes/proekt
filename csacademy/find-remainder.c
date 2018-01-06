#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

#define swap(a,b) do\
    {\
      a ^= b;\
      b ^= a;\
      a ^= b;\
    } while (0)

typedef long long ll;
ll min(ll a, ll b){return a<b?a:b;}
ll max(ll a, ll b){return a>b?a:b;}

ll a[100005], b[100005], c[100005];

ll nod(ll a, ll b){
    if (a > b) 
        swap(a, b);
    if (a == 0)
        return b;
    return nod(b % a, a);
}
int main(){
    int n;
    ll k = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &a[i]);
    for (int i = 1; i <= n; i++){
        scanf("%lld", &b[i]);
        k = max(k, b[i] + 1);
    }
    ll tek = 0;
    for (int i = 1; i <= n; i++){
        if (a[i] < b[i])
            return puts("-1")*0;
        c[i] = a[i] - b[i];
        if (c[i] != 0)
            tek = nod(tek, c[i]);
    }
    if (tek == 0)
        return printf("%lld\n", k)*0;
    bool f = false;
    ll ans = (ll) 1e9 + 7;
    for (ll i = 1; i * i <= tek; i++){
        if (tek % i == 0 && i >= k){
            ans = min(ans, i), f = true;
        }
        if (tek % i == 0 && tek / i >= k) {
            ans = min(ans, tek / i), f = true;
        }
    }
    if (!f)
        puts("-1");
    else
        printf("%lld\n", ans);
    return 0;
}
