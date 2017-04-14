#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>
typedef long long ll;
ll min(ll a,ll b){return a<b?a:b;}
ll max(ll a,ll b){return a>b?a:b;}

typedef long double ld;
typedef unsigned long long ull;

enum{ N = (int)1e5 + 5};
int n;
ll dp[N][2];
int a[N];
int min_element(int*arr,int sz){
    int mine=arr[0];
    for(int i=1;i<sz;i++)
        if(arr[i]<mine)
            mine=arr[i];
    return mine;
}
int main(){ 
	scanf("%d",&n);
	for(int i = 0; i < n; i++)
		scanf("%d", &a[i]);
	ll ans, best;
	ans = best = dp[0][0] = a[0];
	dp[0][1] =(ll) -1e9;
	for(int i = 1; i < n; i++){
		dp[i][0] = max(1LL * a[i], dp[i - 1][0] + a[i]);
		dp[i][1] = max(best + a[i], dp[i - 1][1] + a[i]);
		dp[i][1] = max(dp[i][1], 1LL * a[i]);
		best = max(best, dp[i][0]);
		ans = max(ans, dp[i][1]);
	}
    ll sum=0;
    for(int i=0;i<n;i++)sum+=a[i];
	if(ans == sum)
		ans -= min_element(a, n);
	printf("%lld\n", ans );
}
	
	
	
	
	
	
	
	
	
	
	
	
