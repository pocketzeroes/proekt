#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
enum{MOD = 12345647, MAX_LEN = 10001};
char N[MAX_LEN+1], L[MAX_LEN+1];
int lenN, lenL;
inline int two(int n) { return 1<<n; }
inline int test(int n, int b) { return n & two(b); }
int dp[MAX_LEN][8][3];

int solve(int i, int is_bigger, int carry){
    if (i == lenN)
        return carry ? 0 : 1;
#define result dp[i][is_bigger][carry]
    if (result != -1)
        return result;
    result = 0;
    for (int d1 = test(is_bigger, 0) ? 0 : L[i]; d1 <= 9; ++d1) {
        if (d1 == 3) 
            continue;
        for (int d2 = test(is_bigger, 1) ? 0 : L[i]; d2 <= 9; ++d2) {
            if (d2 == 3) 
                continue;
            for (int d3 = test(is_bigger, 2) ? 0 : L[i]; d3 <= 9; ++d3) {
                if (d3 == 3) 
                    continue;
                int is_bigger2 = is_bigger;
                if (d1 > L[i]) is_bigger2 |= two(0);
                if (d2 > L[i]) is_bigger2 |= two(1);
                if (d3 > L[i]) is_bigger2 |= two(2);
                int carry2 = carry * 10 + N[i] - d1 - d2 - d3;
                if (0 <= carry2 && carry2 <= 2){
                    result = (result + solve(i+1, is_bigger2, carry2)) % MOD;
                }
            }
        }
    }
    return result;
}
int main() {
    int tc;
    scanf("%d", &tc);
    for(int z=0;z<tc;z++){
        scanf("%s %s", N, L);
        if (N[0] == '0' && L[0] == '0') break;
        lenN = strlen(N);
        lenL = strlen(L);
        for (int i = 0; i < lenN; ++i)
            N[i] -= '0';
        for (int i = lenL-1; i >= 0; --i)
            L[i+lenN-lenL] = L[i]-'0';
        for (int i = 0; i < lenN-lenL; ++i)
            L[i] = 0;
        memset(dp, -1, sizeof(dp));
        printf("%d\n", solve(0, 0, 0));
    }
    return 0;
}
