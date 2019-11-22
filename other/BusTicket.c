#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
enum{ MAXN =((int) 1e6 + 2)};

int trips[MAXN], s, p, m, n;
long long dp[MAXN];

int main(){
    scanf("%d %d %d %d", &s, &p, &m, &n);
    for(int i=0; i<n; i++)
        scanf("%d", &trips[i]);
    int tail = 0;
    for(int i=0; i<n; i++){
        while(trips[tail] <= trips[i] - m)
            tail++;
        dp[i+1] = fminl(s + dp[i], p + dp[tail]);
    }
    printf("%lld\n", dp[n]);
    return 0;
}
