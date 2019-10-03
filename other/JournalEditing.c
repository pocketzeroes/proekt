#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef struct{
  int first;
  int second;
}pair;
void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}

int main(){
    int n;
    scanf("%d", &n);
    pair*thms[n];
    int sizes[n];
    for(int z=0;z<n;z++){
        int ps;
        scanf("%d", &ps);
        thms[z] = calloc(ps, sizeof(pair));
        sizes[z]=ps;
        for(int q=0;q<ps;q++){
            int deps, d;
            scanf("%d %d", &thms[z][q].first, &deps);
            while(deps--){
                scanf("%d", &d);
                thms[z][q].second |= 1<<d;
            }
        }
    }
    int inf =(int)1e9;
    int ans = inf;
    int dp[1<<n]; fill(dp, 1<<n, inf);
    dp[0] = 0;
    for(int m=0; m<(1<<n); ++m){
        if(dp[m] == inf) 
            continue;
        if(m&1)
            ans = fmin(ans, dp[m]);
        for(int i=0; i<n; ++i){
            if((m&(1<<i)) == 0){
                for(int z=0;z<sizes[i];z++){pair p = thms[i][z];
                    if((m&p.second) == p.second){
                        dp[m|(1<<i)] = fmin(dp[m|(1<<i)], dp[m]+p.first);
                    }
                }
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}
