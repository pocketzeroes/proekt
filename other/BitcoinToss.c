#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void solve(){
    char string[20005];
    scanf("%s", string);
    int len = strlen(string);
    for (int n = 10; n >= 0; --n){
        int charsNeeded = n * (1 << n);
        if (charsNeeded > len) 
            continue;
        int p = 0;
        while (p + charsNeeded <= len){
            int* dp = (int*) calloc((1<<n), sizeof(int));
            int passed = 1;
            for (int num = 0; num < (1<<n); ++num){
                int startingChar = p + num*n;
                int mask = 0;
                for (int i = 0; i < n; ++i){
                    if (string[startingChar + i] == 'H'){
                        mask ^= (1 << i);
                    }
                }
                if (dp[mask]){
                    passed = 0;
                    break;
                }
                dp[mask] = 1;
            }
            if (passed){
                printf("%d %d\n", n, p);
                return;
            }
            ++p;
        }
    }
}
int main(){
    int testcases;
    scanf("%d", &testcases);
    for (int i = 0; i < testcases; ++i){
        solve();
    }
    return 0;
}
