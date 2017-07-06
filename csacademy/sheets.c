#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
       
typedef long long ll;

int q;
int t, k;
ll x;
  
const bool is_testing = 0;

int main() { 
    scanf("%d", &q);
    while(q--){
    	scanf("%d %d %lld", &t, &k, &x);
    	x--;
    	if (k == 0){
    		puts("1");
    		continue;
    	}
    	if (t == 1){
    		ll str = (ll)1 << k;
    		ll num = 0;
    		ll sh = 1;
    		ll xx = x / str;
    		ll yy = x % str;
    		for (int i = k; i >= 1; i--){
    			str /= (ll)2;
    			if (xx >= str){
    				num = sh + (sh - num - 1);
    				xx = str * (ll)2 - xx - 1;
    			}
    			sh *= (ll)2;
    			if (yy >= str){
    				num = sh + (sh - num - 1);
    				yy = str * (ll)2 - yy - 1;
    			}
    			sh *= (ll)2;
    		}
    		printf("%lld\n", num + 1);
    	}
        else {
    		ll num = x;
    		ll sh = (ll)1 << (2 * k);
    		ll xx = 0; 
    		ll yy = 0;
    		ll str = 1;
    		for (int i = k; i >= 1; i--){
    			sh /= (ll)2;
    			str *= 2;
    			if (num >= sh){
    				num = 2 * (ll)sh - num - 1;
    				yy = str - yy - 1;
    			}
    			sh /= (ll)2;
    			if (num >= sh){
    				num = 2 * (ll)sh - num - 1;
    				xx = str - xx - 1;
    			}
    		}
    		printf("%lld\n", xx * ((ll)1 << k) + yy + 1 );
    	}
    }
}


















































