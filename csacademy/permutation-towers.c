#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}


enum{ kMaxN = 103   };
enum{ kMaxX = 100200};
int mod;
int dp[kMaxN][2 * kMaxN * kMaxN];
int next_dp[kMaxN][2 * kMaxN * kMaxN];
int fact[kMaxX + 1], inv_fact[kMaxX + 1];

int Comb(int a, int b) {
    return 1LL * fact[a] * inv_fact[b] % mod * inv_fact[a - b] % mod;
}
int Pow(int a, int p){
    int r = 1;
    while (p) {
        if (p & 1) {
            r = 1LL * r * a % mod;
        }
        a = 1LL * a * a % mod;
        p /= 2;
    }
    return r;
}
int Mod(int*a){
    if(*a >= mod)
        return (*a) -= mod;
    else if(*a < 0)
        return (*a) += mod;
    else
        return *a;
}
int main(){
    int n, x;
    scanf("%d %d %d", &n, &x, &mod);
    dp[0][1] = 1;
    dp[1][n] = 2;
    dp[2][n * 2 - 1] = 1;
    int mx_dist = n * 2 - 1;
    for (int i = n - 1; i; i -= 1) {
        for (int num = 1; num <= min(i, (n - i) * 2); num += 1){
            for (int dist = 0; dist <= mx_dist; dist += 1){
                if (dp[num][dist] == 0){
                    continue;
                }

                next_dp[num - 1][1 + dist]             += 1LL * num * dp[num][dist] % mod;Mod(&next_dp[num - 1][1 + dist]            );
                next_dp[num][1 + dist + i - 1]         += 2LL * num * dp[num][dist] % mod;Mod(&next_dp[num][1 + dist + i - 1]        );
                next_dp[num + 1][1 + dist + 2 * i - 2] += 1LL * num * dp[num][dist] % mod;Mod(&next_dp[num + 1][1 + dist + 2 * i - 2]);
            }
        }
        mx_dist += 2 * i - 1;
        for (int a = 0; a <= min(i, (n - 1) * 2) + 1; a += 1){
            for (int b = 0; b <= mx_dist; b += 1){
                dp[a][b] = next_dp[a][b];
                next_dp[a][b] = 0;
            }
        }
    }
    fact[0] = 1;
    for (int i = 1; i <= x + n; i += 1){
        fact[i] = 1LL * fact[i - 1] * i % mod;
    }
    inv_fact[x + n] = Pow(fact[x + n], mod - 2);
    for (int i = x + n - 1; i >= 0; i -= 1){
        inv_fact[i] = 1LL * (i + 1) * inv_fact[i + 1] % mod;
    }
    int ans = 0;
    for (int i = 0; i < min(2 * kMaxN *  kMaxN, x + 1); i += 1){
        ans += 1LL * Comb(x - i + n, n) * dp[0][i] % mod;
        Mod(&ans);
    }
    printf("%d\n", ans);
    return 0;
}
































































