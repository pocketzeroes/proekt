#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;

ll n;
ll rec(int pos, ll p3){
    if(pos < 0)
        return 0;
    if(n & (1LL << pos))
        return 2*rec(pos-1, p3 / 3) + p3;
    return rec(pos-1, p3 / 3);
}
int main(){
    scanf("%lld", &n);
    ll p3 = 1;
    for(int i = 0; i < 38; i++)
        p3 *= 3;
    printf("%lld\n", rec(38, p3) );
    return 0;
}
