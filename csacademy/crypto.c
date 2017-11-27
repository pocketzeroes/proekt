#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
typedef long long ll;
enum{ N   =(int) 4e2+10};
enum{ MOD =(int) 1e9+7 };
int n, k, p;
ll f[N][N*N];
int main(){
    scanf("%d %d %d", &n, &k, &p);
    if(p > n*n){
        puts("0");
        return 0;
    }
    f[k][1] = 1;
    for(int i=1; i<=k; i++)
        f[k][1] = ( f[k][1]*i )%MOD;
    for(int i=k; i<n; i++){
        int cur = i , max_acc = min( i-k+2 , k );
        for(int j=1;j<=p;j++){
            if (f[cur][j]){
                int left = ( i+1 ) - 2*( max_acc-1 );
                f[cur+1][j+1] = ( f[cur+1][j+1] + 2*f[cur][j] ) % MOD;
                f[cur+1][j+max_acc] = ( f[cur+1][j+max_acc] - 2*f[cur][j] + left*f[cur][j]) % MOD;
                f[cur+1][j+max_acc+1] = ( f[cur+1][j+max_acc+1] - left*f[cur][j] ) % MOD;
            }
        }
        for(int j=1; j<=p; j++)
            f[cur+1][j] = ( f[cur+1][j] + f[cur+1][j-1] ) % MOD;
    }
    ll rv = ( f[n][p] + MOD ) % MOD;
    printf("%lld\n", rv);
    return 0;
}
