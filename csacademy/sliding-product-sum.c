#pragma GCC optimize("O3")
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

long long N, K, M;

inline long long mod(long long a, long long m) {
    return (a % m + m) % m;
}
//inline
long long mul(long long a, long long b, long long m) {
    a = mod(a, m); b = mod(b, m);
    if (b == 0) return 0;
    long long res = mul(mod(a + a, m), b>>1, m);
    if (b & 1) res = mod(res + a, m);
    return res;
}
long long solve() {
    long long res = 0;
    for (long long k = 1; k <= K; ++k) {
        long long tmp = 1;
        bool ok = false;
        for (long long num = N-k+1; num <= N+1; ++num) {
            long long tnum = num;
            if (!ok && num % (k+1) == 0) {
                ok = true;
                tnum = num / (k+1);
            }
            tmp = mul(tmp, tnum, M);
        }
        res += tmp;
        res %= M;
    }
    return res;
}
int main(){
    while(scanf("%lld%lld%lld", &N, &K, &M)==3){
        printf("%lld\n", solve());
    }
}
