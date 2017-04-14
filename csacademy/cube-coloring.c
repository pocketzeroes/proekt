#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<limits.h>

typedef long long int64;
enum{ kMaxN =(int) 1e3};

int64 Comb(int a, int b) {
    if (a - b < b) {
        return Comb(a, a - b);
    } 
    else {
        int64 result = 1;
        for (int i = 0; i < b; i += 1) {
            result = result * (a - i);
            result /= (i + 1);
        }
        return result;
    }
}
int64 Solve(int small, int big) {
    const int64 bonus[] = {30, 3, 1, 1};
    int64 result = 0;
    for (int num_big = 0; num_big < 4; num_big += 1) {
        if (num_big > big) {
            continue;
        }
        if (big + small + num_big < 6) {
            continue;
        }
        result += 1LL * bonus[num_big] * Comb(big, num_big) * Comb(big + small - num_big, 6 - 2 * num_big);
    }
    return result;
}
int main() {
    int n;
    scanf("%d", &n);
    assert(1 <= n);
    assert(n <= kMaxN);
    int small = 0, big = 0;
    for (int i = 0; i < n; i += 1) {
        int x; 
        scanf("%d", &x);
        if (x == 1) {
            small += 1;
        } 
        else {
            big += 1;
        }
    }
    int64 rv=Solve(small, big);
    printf("%lld\n", rv);
    return 0;
}


















































