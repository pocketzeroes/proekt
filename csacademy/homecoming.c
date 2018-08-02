#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define max(a,b) (((a)>(b))?(a):(b))
typedef long long ll;
enum{ MOD = 1000000007};
enum{ MX  = 2000001   };
#define INF (ll)1e18
ll cb[2*MX], dp[MX][2][2];

ll get(int l, int r){
    return cb[r+1]-cb[l];
}
ll solve(int N, int K, int*A, int*B){
    for(int i=0; i<2*N; i++)
        cb[i+1] = cb[i]+B[i%N];
    ll ans = 0;
    for(int i=0; i<N; i++) 
        for(int j=0; j<2; j++)
            for(int k=0; k<2; k++) 
                dp[i][j][k] = -INF;
    dp[0][0][0] = 0, dp[0][1][1] = A[0]-get(0,K-1);
    for(int i=1; i<N; i++){
        for(int j=0; j<2; j++){
            dp[i][0][j] = max(dp[i-1][0][j],dp[i-1][1][j]);
            if(j==0 || i+K-1 < N)
                dp[i][1][j] = max(dp[i-1][1][j]+A[i]-B[(i+K-1)%N],dp[i-1][0][j]+A[i]-get(i,i+K-1));
            else
                dp[i][1][j] = max(dp[i-1][1][j]+A[i],dp[i-1][0][j]+A[i]-get(i,N-1));
        }
    }
    for(int j=0; j<2; j++) 
        for(int k=0; k<2; k++) 
            ans = max(ans,dp[N-1][j][k]);
    return ans;
}
int main(){
    int T;
    scanf("%d", &T);
    for(int i=0; i<T; i++){
        int N, K;
        scanf("%d %d", &N, &K);
        int A[N];
        for(int i=0; i<N; i++) 
            scanf("%d", &A[i]);
        int B[N];
        for(int i=0; i<N; i++)
            scanf("%d", &B[i]);
        printf("%lld\n", solve(N, K, A, B) );
    }
    return 0;
}
