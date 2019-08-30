#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
 
typedef long long ll;
 
ll Case;
ll n, d;
ll h[110];
ll number[105*105*2];
ll dp[2][105*105*2];
ll INF = (1LL << 60);
int cmpLL(const void*pa, const void*pb){
  ll*a =(ll*)pa;
  ll*b =(ll*)pb;
  return(*a < *b)?-1:1;
}
int unique(ll*a, int len){
	int i, j;
	for(i = j = 0; i < len; i++)
		if (a[i] != a[j])
      a[++j] = a[i];
	return j + 1;
}
int main(){
    scanf("%lld", &Case);
    while(Case--){
        scanf("%lld%lld", &n, &d);
        for(ll i = 0; i < n; i++)
            scanf("%lld", &h[i]);
        if(llabs(h[n - 1] - h[0])>(n - 1)*d){
            puts("impossible");
            continue;
        }
        ll amount = 0;
        for (ll i = 0; i < n; i++)
            for (ll k = -(n - 1); k <= n - 1; k++)
                number[amount++] = h[i] + k*d;
        qsort(number, amount, sizeof(ll), cmpLL);
        amount = unique(number, amount);
        int ind = 0;
        for (int j = 0; j < amount;j++){
            dp[ind][j] = INF;
            if (number[j] == h[0])
                dp[ind][j] = 0;
        }
        for (ll i = 1; i < n; i++){
            ll k = 0;
            for (ll j = 0; j < amount; j++){
                while (k < amount&&number[k] < number[j] - d)
                    k++;
                while (k + 1 < amount&&number[k + 1] <= number[j] + d&&dp[ind][k+1]<=dp[ind][k])
                    k++;
                if (dp[ind][k] == INF)
                    dp[ind ^ 1][j] = INF;
                else
                    dp[ind ^ 1][j] = dp[ind][k] + llabs(h[i]-number[j]);
            }
            ind = ind ^ 1;
        }
        for(int i = 0; i < amount; i++){
            if(number[i] == h[n - 1]){
                printf("%lld\n", dp[ind][i]);
                break;
            }
        }
    }
    return 0;
}
