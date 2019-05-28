#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

enum{ MAXT = 100000};
int dp[MAXT +  100], N, T, a, b, t, Q;

int main(){
    for(int i = 0; i <= MAXT; i++)
        dp[i] = 0;
    scanf("%d", &N);
    T = MAXT;
    while(N--){
        scanf("%d %d %d", &a, &b, &t);
        if(b){
            for(int k = 0; true; ++k){
                int fun = a - b * k * k;
                if(fun < 0)
                    break;
                for(int ct = T; ct >= t; ct--)
                    dp[ct] = max(dp[ct], dp[ct-t] + fun);
            }
        }
        else {
            for(int ct = t; ct <= T; ct++)
                dp[ct] = max(dp[ct], dp[ct-t] + a);
        }
    }
    scanf("%d", &Q);
    while(Q--){
        scanf("%d", &T);
        printf("%d\n", dp[T]);
    }
    return 0;
}
