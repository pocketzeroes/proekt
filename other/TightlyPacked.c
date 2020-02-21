#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;

ll lSqrt(ll N){
    if(N <= 1)
        return N;
    ll maxSqrt = 1;
    while(maxSqrt * maxSqrt <= N)
        maxSqrt *= 2LL;
    ll minSqrt = maxSqrt / 2LL;
    while(minSqrt < maxSqrt){
        ll mid = (minSqrt + maxSqrt) / 2LL;
        ll sqr = mid*mid;
        if(sqr == N)
            return mid;
        else if(sqr < N)
            minSqrt = mid + 1;
        else
            maxSqrt = mid;
    }
    return minSqrt-1LL;
}
ll pack(ll N){
    ll bestSoFar = LLONG_MAX;
    ll stop = lSqrt(N)+1;
    ll start = fmaxl(1LL, 7 * (stop-1LL) / 10);
    for(ll h = start; h <= stop; ++h){
        ll w = N / h;
        if(2*h >= w){
            if(h*w == N){
                bestSoFar = 0;
                break;
            }
            else{
                ++w;
                if(2*h >= w){
                    ll boxSize = h*w;
                    bestSoFar = fminl(bestSoFar, boxSize - N);
                }
            }
        }
    }
    return bestSoFar;
}
int main(){
    ll N;
    scanf("%lld", &N);
    ll empty = pack(N);
    printf("%lld\n", empty);
    return 0;
}
