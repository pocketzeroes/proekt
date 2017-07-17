#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>
typedef long long ll;
ll min(ll a,ll b){return a<b?a:b;}
ll max(ll a,ll b){return a>b?a:b;}

ll max_element(ll*arr,int sz){
    ll maxe=arr[0];
    for(int i=1;i<sz;i++)
        if(arr[i]>maxe)
            maxe=arr[i];
    return maxe;
}

ll a[4];

int main(){
	for (int i = 0; i < 4; i += 1) {
	    scanf("%lld", &a[i]);
	}
	ll ans = max_element(a, 4);
	for (int i = 0; i < 4; i += 1) {
	    ll minn = 1LL << 40;
	    for (int j = 0; j < 4; j += 1) {
	        if (j != i) {
	            minn = min(minn, a[j]);
	        }
	    }
	    ans = max(ans, a[i] + minn);
	}
	for (int i = 0; i < 4; i += 1) {
	    for (int j = 0; j < 4; j += 1) {
	        if (i != j) {
	            ll minn = 1LL << 40;
        	    for (int k = 0; k < 4; k += 1) {
        	        if (k != i && k != j) {
        	            minn = min(minn, a[k]);
        	        }
        	    }
        	    ll initial_moves = min(minn, a[j]);
        	    ll x = a[i] + 2 * initial_moves;
        	    if (minn >= initial_moves) {
        	        minn -= initial_moves;
        	        x += minn / 3 * 3;
        	        if (minn % 3 == 2) {
        	            x += 1;
        	        }
        	    }
        	    ans = max(ans, x);
	        }
	    }
	}
	printf("%lld\n", ans);
	return 0;
}




