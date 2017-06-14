#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>


enum{ kMod  =(int) 1e9+7}; 
enum{ kMaxN =(int) 1e5+5};

int n, k;
int dp[kMaxN];
int inv_dp_sum[kMaxN];


int Mod(int*a) {
    if (*a >= kMod) {
        *a -= kMod;
    } else if (*a < 0) {
        *a += kMod;
    }
    return *a;
}
int Pow(int a, int p) {
    int r = 1;
    while (p) {
        if (p & 1) {
            r = 1LL * r * a % kMod;
        }
        a = 1LL * a * a % kMod;
        p /= 2;
    }
    return r;
}
int Inv(int a) {
    return Pow(a, kMod - 2);
}
int NumPalindroms(int pos) {
    return Pow(k, (pos + 1) / 2);
}
int main(){
    scanf("%d %d", &n, &k);
    for (int len = 1; len <= n; len += 1) {
        int start = NumPalindroms(len);
        start -= 1LL * inv_dp_sum[(len + 1) / 2] * Pow(k, (len + 1) / 2) % kMod;
        Mod(&start);
        int num_bad = 1LL * start * Inv(Pow(k, len)) % kMod;
        if (len == 1) {
            num_bad = 0;
        }
        inv_dp_sum[len] = inv_dp_sum[len - 1];
        inv_dp_sum[len] += num_bad;
        Mod(&inv_dp_sum[len]);
        dp[len] = start;
    }
    printf("%d\n", dp[n]);
    return 0;
}




















































