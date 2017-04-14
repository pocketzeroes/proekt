#include<stdio.h>

typedef struct pair{
    int first;
    int second;
}pair;
pair newPair(int a, int b){
    pair rez;
    rez.first =a;
    rez.second=b;
    return rez;
}

enum{ kMaxN =(int) 1e4+1}; 
enum{ kMod  =(int) 1e9+7};

pair dp[kMaxN];

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    dp[0] = newPair(1, 0);
    for (int i = 1; i <= k; i += 1) {
        for (int s = 0; s + i <= n; s += 1) {
            dp[i + s].first  = (dp[i + s].first + dp[s].first) % kMod;
            dp[i + s].second = (dp[i + s].second + dp[s].second + 1LL * dp[s].first * (2 * s + i)) % kMod;
        }
    }
    int rez = (dp[n - k].second + 1LL * dp[n - k].first * (2 * (n - k) + k)) % kMod;
    printf("%d",rez);
    return 0;
}
