#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>
typedef long long ll;
enum{ N = 100100};
int n;
int k;
int a[N];

int f(int x){
    int c = x;
    for(int i = 1; i <= n; i++)
        c -= (a[i] <= x);
    return c;
}
int main(){
    scanf("%d %d", &n, &k);
    for(int i=1; i<=n; i++)
        scanf("%d", &a[i]);
    int l = 0, 
        r = 1e9 + n;
    while(l < r){
        int m = (l + r) / 2;
        if(f(m) < k)
            l = m + 1;
        else
            r = m;
    }
    ll s = 0;
    for(int i=1; i<=n; i++)
        if(a[i] <= l)
            s += a[i];
    printf("%lld\n", 1ll * l * (l + 1) / 2 - s);
    return 0;
}
