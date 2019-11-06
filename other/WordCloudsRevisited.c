#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ MAXN = 5000};
enum{ INF  = MAXN*150};
int w[MAXN];
int h[MAXN];
int opt[MAXN+1];

int main(){
    int N,W;
    scanf("%d %d", &N, &W);
    for(int j=0; j < N; j++)
        scanf("%d %d", &w[j], &h[j]);
    opt[N] = 0;
    for (int j=N-1; j >= 0; j--){
        int rowH = 0;
        int rowW = 0;
        int best = INF;
        for (int k=j; k < N; k++) {
            rowH = fmax(rowH, h[k]);
            rowW += w[k];
            if (rowW <= W){
                best = fmin(best, rowH + opt[k+1]);
            }
            else
                break;
        }
        opt[j] = best;
    }
    printf("%d\n", opt[0]);
    return 0;
}
