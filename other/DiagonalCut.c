#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;

ll gcd(ll a, ll b){
    if(b == 0)
        return a;
    return gcd(b, a%b);
}
int main(){
    ll x, y;
    scanf("%lld %lld", &x, &y);
    ll g = gcd(x, y);
    x = x/g;
    y = y/g;
    if(x%2 == 0 || y%2 == 0)
        puts("0");
    else
        printf("%lld\n", g);
    return 0;
}
