#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
enum{ MaxN =(int) 1e5 + 15};
ll gn, k;
ll a[MaxN];

void solve(ll x, ll y){
    for(int i = 1; i <= k; ++i)
        if(i & 1)
            printf("%lld ", x);
        else
            printf("%lld ", y);
    exit(0);
}
void can(ll d){
    ll n = gn;
    for(int i = 1; i <= k; i += 2){
        a[i] = d + 1;
        n -= d + 1;
    }
    for(int i = 2; i <= k; i += 2){
        a[i] = d - 1;
        n -= d - 1;
    }
    n = -n;
    if(n > 0){
        if(k - k / 2 < n)
            return;
        for(int i = 1; i <= k && n; i += 2)
            --a[i], --n;
        for(int i = 1; i <= k; ++i)
            printf("%lld ", a[i]);
        exit(0);
    }
    else{
        if(k / 2 <= -n)
            return;
        for(int i = 2; i <= k && n != 0; i += 2)
            ++a[i], ++n;
        for(int i = 1; i <= k; ++i)
            printf("%lld ", a[i]);
        exit(0);
    }
}
void can1(ll d){
    ll n = gn;
    for(int i = 1; i <= k; i += 2){
        a[i] = d - 1;
        n -= d - 1;
    }
    for(int i = 2; i <= k; i += 2){
        a[i] = d + 1;
        n -= d + 1;
    }
    n = -n;
    if(n > 0){
        if(k / 2 < n)
            return;
        for(int i = 2; i <= k && n; i += 2)
            --a[i], --n;
        for(int i = 1; i <= k; ++i)
            printf("%lld ", a[i]);
        exit(0);
    }
    else{
        if(k - k / 2 <= -n)
            return;
        for(int i = 1; i <= k && n != 0; i += 2)
            ++a[i], ++n;
        for(int i = 1; i <= k; ++i)
            printf("%lld ", a[i]);
        exit(0);
    }
}
bool check(){
    ll d = gn / k;
    ll k1 = k - k / 2;
    ll k2 = k - k1;
    for(ll i = d - 10; i <= d + 10; ++i)
        if(i > 0){
            if(k1 * i + k2 * (i + 1) == gn)
                solve(i, i + 1);
            if(k1 * (i + 1) + k2 * i == gn)
                solve(i + 1, i);
        }
    for(ll i = d - 10; i <= d + 10; ++i)
        if(i > 1){
            can(i);
            can1(i);
        }
}
int main(){
    scanf("%lld %lld", &gn, &k);
    check();
    puts("-1");
    return 0;
}


