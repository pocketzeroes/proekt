#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
enum{ kInf  = 0x3f3f3f3f};
enum{ kMaxN = 104744    };
int not_prime[kMaxN];
int primes   [kMaxN];

int main() {
    int num_primes = 1e4;
    for (int num_div = 0, d = 2; d < kMaxN && num_div <= num_primes; d += 1) {
        if (not_prime[d]) {
            continue;
        }
        for (ll j = 1LL * d * d; j < kMaxN; j += d) {
            not_prime[j] = true;
        }
        primes[num_div++] = d;
    }
    int n, k;
    scanf("%d %d", &n, &k);
    k = (n) * (n - 1) / 2 - k;
    int first_batch = 2;
    while (1LL * first_batch * (first_batch - 1) / 2 <= k) {
        first_batch += 1;
    }
    first_batch -= 1;
    for (int i = 2; i <= first_batch; i += 1) {
        primes[i] *= 3;
    }
    k -= first_batch * (first_batch - 1) / 2;
    if (k) {
        primes[first_batch + 1] *= 2;
        for (int i = 1; i <= k; i += 1) {
            primes[i] *= 2;   
        }
    }
    for (int i = 1; i <= n; i += 1) {
        printf("%d ", primes[i]);
    }
    return 0;
}
























































