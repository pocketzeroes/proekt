#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int res[110];

void recursive(int now, int prev, int N, int K) {
    if (now > K) {
        for (int i = 1; i <=K; i++) 
            printf("%d ", res[i]);
        puts("");
        return;
    }
    for (int i = prev+1; i<=N-(K-now); i++) {
        res[now] = i;
        recursive(now+1, i, N, K);
    }
}

void generateCombinations(int N, int K) {
    recursive(1,0,N,K);    
}
int main() {
    int N, K;
    scanf("%d %d", &N, &K);
    generateCombinations(N, K);
    return 0;
}
