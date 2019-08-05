#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))

typedef long long ll;
const ll INF=(ll)1e18;
ll w[20],h[20],q[20];
ll d[1<<15][20];
ll ans[1<<15];

ll min_element(ll*arr, int sz){
    ll mine = arr[0];
    for(int i=1;i<sz;i++)
        if(arr[i]<mine)
            mine=arr[i];
    return mine;
}
int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    for(int i=0; i<n; i++)
        scanf("%lld %lld %lld", &w[i], &h[i], &q[i]);
    for(int i=0; i<(1<<n); i++){
        ll cnt=0, area=0, H=0, W=0;
        for(int j=0; j<n; j++){
            if((1<<j)&i){
                W = max(W,w[j]);
                H = max(H,h[j]);
                cnt += q[j];
                area += w[j]*h[j]*q[j];
            }
        }
        ans[i] = cnt*W*H-area;
    }
    for(int i=0; i<(1<<n); i++)
        for(int j=0; j<=m; j++)
            d[i][j] = INF;
    d[0][0] = 0;
    for(int i=0; i<(1<<n); i++){
        int S = ((1<<n)-1)^i;
        for(int j=S; j; j=(j-1)&S)
            for(int k=0; k<m; k++)
                d[i^j][k+1] = min(d[i^j][k+1],d[i][k]+ans[j]);
    }
    printf("%lld\n", min_element(d[(1<<n)-1], m+1));
    return 0;
}
