#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
char buff[100000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}

enum{ N = 5005, MOD =(int)1e9 + 7};
int dp[N], hint2[N], hint1[N];

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    for(int i=1; i<=n; ++i){
        hint1[i] = i;
        hint2[i] = 0;
    }
    for(int i=0; i<m; ++i){
        int x, l, r;
        char*s;
        scanf("%d %d", &l, &r);
        s = getstr();
        (s[0] == 's') ? (x=1) : (x=2);
        if(x == 1)
            hint1[r] = fmin(hint1[r], l);
        else
            hint2[r] = fmax(hint2[r], l);
    }
    dp[0] = 1;
    for(int i = 1; i <= n; ++ i){
        int h1 = i, h2 = 0;
        for(int j = i; j >= 1; -- j){
            h2 = fmax(h2, hint2[j]);
            h1 = fmin(h1, hint1[j]);
            if (j > h2 && j <= h1){
                dp[i] += dp[j - 1];
                dp[i] %= MOD;
            }
        }
    }
    printf("%d\n", (dp[n] * 2)%MOD);
    return 0;
}
