#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
enum{ MAXNQ = 200005, BSZ = 500};
int N, Q;
ll A[MAXNQ], B[BSZ][BSZ];

int main(){
    scanf("%d %d", &N, &Q);
    for (int i = 1; i <= N; i++) 
        A[i] = 0;
    for (int i = 1; i < BSZ; i++) 
        for (int j = 0; j < i; j++) 
            B[i][j] = 0;
    for (int i = 0, t, a, b, c; i < Q; i++){
        scanf("%d", &t);
        if (t == 1){
            scanf("%d %d %d", &a, &b, &c);
            a %= b;
            if (b >= BSZ) 
                for (int j = a; j <= N; j += b) 
                    A[j] += c;
            else 
                B[b][a] += c;
        }
        else {
            scanf("%d", &a);
            ll ans = A[a];
            for (int j = 1; j < BSZ; j++) 
                ans += B[j][a % j];
            printf("%lld\n", ans);
        }
    }
    return 0;
}
