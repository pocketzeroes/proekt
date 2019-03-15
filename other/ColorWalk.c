#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

bool edge[2][16][16];
bool dp[16][65536];

int main(){
    int n;
    scanf("%d", &n);
    for(int i=0; i<n; ++i){
        int size;
        scanf("%d", &size);
        for (int color = 0; color <= 1; ++color){
            for (int j = 0; j < size; ++j){
                for (int k = 0; k < size; ++k){
                    scanf("%d", &edge[color][j][k]);
                }
            }
        }
        int result = 0;
        for (int qlen = 1; qlen <= size; ++qlen){
            memset(dp, 0, sizeof(dp));
            for (bool updated = true; updated; ){
                updated = false;
                for (int j = 0; j < size; ++j){
                    for (int q = 0; q < 1 << qlen; ++q){
                        if (dp[j][q]) 
                            continue;
                        int color = q & 1;
                        int rejected = true;
                        for (int k = 0; k < size; ++k){
                            if (edge[color][j][k]){
                                rejected &= dp[k][(q >> 1) | (1 << (qlen - 1))] || dp[k][q >> 1];
                            }
                        }
                        dp[j][q] = rejected;
                        updated |= rejected;
                    }
                }
            }
            bool fail = false;
            for (int q = 0; q < 1 << qlen; ++q) {
                fail |= dp[0][q];
            }
            if (!fail) {
                result = qlen;
                break;
            }
        }
        printf("%d\n", result);
    }
    return 0;
}
