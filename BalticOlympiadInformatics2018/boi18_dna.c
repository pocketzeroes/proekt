#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}

int main(){
    int N, K, R;
    scanf("%d %d %d", &N, &K, &R);
    int dna[N];
    for(int i=0; i<N; ++i){
        scanf("%d", &dna[i]);
    }
    int need[K+1]; memset(need, 0, sizeof(need));
    for(int i=0; i<R; ++i){
        int B, Q;
        scanf("%d %d", &B, &Q);
        need[B] = Q;
    }
    int bad = R;
    int r   = 0;
    int ans = N+1;
    for(int l = 0; l < N; l++){
        while (bad > 0 && r < N){
            need[dna[r]]--;
            if (need[dna[r]] == 0)
                --bad;
            r++;
        }
        if (bad == 0)
            ans = min(ans, r-l);
        need[dna[l]]++;
        if (need[dna[l]] == 1)
            ++bad;
    }
    if (ans == N+1)
        puts("impossible");
    else
        printf("%d\n", ans);
    return 0;
}
