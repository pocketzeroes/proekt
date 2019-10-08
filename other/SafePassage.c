#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int n;
int load[15];
int min_cost_go [1 << 15];
int min_cost_ret[1 << 15];

int main(){
    scanf("%d", &n);
    for(int i = 0; i < n; ++i)
        scanf("%d", &load[i]);
    for (int i = 0; i < 1 << n; ++i){
        min_cost_go [i] = 1 << 30;
        min_cost_ret[i] = 1 << 30;
    }
    min_cost_ret[0] = 0;
    for (int iter = 0; true; ++iter){
        for (int i = 0; i < 1 << n; ++i){
            for (int j = 0; j < n - 1; ++j){
                if (i & (1 << j)) 
                    continue;
                for (int k = j + 1; k < n; ++k){
                    if (i & (1 << k)) 
                        continue;
                    min_cost_go[i | (1 << j) | (1 << k)] = fmin(
                        min_cost_go[i | (1 << j) | (1 << k)],
                        min_cost_ret[i] + fmax(load[j], load[k])
                    );
                }
            }
        }
        if (iter == n - 2) {
            printf("%d\n", min_cost_go[(1 << n) - 1]);
            return 0;
        }
        for (int i = 0; i < 1 << n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (~(i | ~(1 << j))) 
                    continue;
                min_cost_ret[i & ~(1 << j)] = fmin(
                    min_cost_ret[i & ~(1 << j)],
                    min_cost_go[i] + load[j]
                );
            }
        }
    }
    return 0;
}
