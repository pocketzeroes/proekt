#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef __int128_t ll;

const long long SCALE = 10000000;

int main(){
    int n;
    scanf("%d", &n);
    ll pts[n];
    for(int i=0; i<n; i++){
        long long x, y;
        scanf("%lld %lld", &x, &y);
        pts[i] = ((-x + y) * SCALE);
    }
    ll countDist(ll a){
        ll dst = 0;
        for(int i=0; i<n; i++){ll p=pts[i];
            ll d = p - a;
            dst += d * d;
        }
        return dst;
    }
    ll lo = -1E8 * SCALE;
    ll hi =  1E8 * SCALE;
    for(int it=0; it<100; it++){
        ll l = (hi - lo) / 3;
        ll m1 = lo + l;
        ll m2 = lo + 2 * l;
        if(countDist(m1) < countDist(m2))
            hi = m2;
        else
            lo = m1;
    }
    printf("%.6lf\n", (double)(hi + lo) / (2 * SCALE));
    return 0;
}
