#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
ll min(ll a,ll b){return a<b?a:b;}
ll max(ll a,ll b){return a>b?a:b;}
enum{ mx = 500000};
int a[mx], n, MIN, MAX;
ll ans = 0;
int main(){
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) 
        scanf("%d", &a[i]);
    MIN = MAX = a[0];
    for (int i = 0; i < n; ++i){
        MIN = min(MIN, a[i]);
        MAX = max(MAX, a[i]);
    }
    for (int i = 0; i < n; ++i){
        if (a[i] != MIN && a[i] != MAX)
            ans += a[i];
    }
    printf("%lld", ans);
    return 0;
}
