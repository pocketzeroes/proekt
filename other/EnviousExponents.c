#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;

enum{ B = 62};

int main(){
    ll N;
    int K;
    scanf("%lld %d", &N, &K);
    ll bits[B]; memset(bits, 0, sizeof(bits));
    int sofar = 0, zero = 1;
    for(int i = B-1; i >= 0; --i){
        bits[i] = (N>>i)&zero;
        if (!bits[i])
            continue;
        sofar++;
        if (sofar == K){
            bits[i] = zero = 0;
            --sofar;
            for (int j = i + 1; j < B; ++j){
                bits[j] = !bits[j];
                sofar += bits[j] ? 1 : -1;
                if (bits[j])
                    break;
            }
        }
    }
    ll ans = 0LL;
    for (int i = 0; i < B; ++i){
        if (sofar < K && !bits[i])
            bits[i] = 1, ++sofar;
        ans |= bits[i] << i;
    }
    printf("%lld", ans);
    return 0;
}
