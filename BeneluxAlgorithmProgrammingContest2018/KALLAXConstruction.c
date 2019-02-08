#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
typedef struct{
    ll first;
    ll second;
}pair;
pair newPair(ll a, ll b){
    pair rez;
    rez.first =a;
    rez.second=b;
    return rez;
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
pair*pushback(pair*array, int *size, pair value){
    pair*output = resizeArray(array, pair, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	pair*ptr;
	int sz;
}vecp;
vecp newVecP() {
	vecp rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
enum{ BMAX = 2001};
void fill(ll*arr, int sz, ll val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
ll dp[BMAX+1];


int main() {
    ll B;
    int K;
    scanf("%lld %d", &B, &K);
    vecp*prices = calloc(K, sizeof(vecp));
    for(int i=0; i<K; ++i){
        fill(dp, BMAX+1, -1);
        dp[0] = 0LL;
        if(i > 0){
            for(int z=0;z<prices[i-1].sz;z++){pair price = prices[i-1].ptr[z];
                ll sticker= price.first;
                ll real   = price.second;
                for(int j=0; j<=BMAX-sticker; ++j){
                    if(dp[j] >= 0LL){
                        ll new_real = dp[j] + real;
                        if(dp[j+sticker] > new_real || dp[j+sticker] < 0)
                           dp[j+sticker] = new_real;
                    }
                }
            }
        }
        int L, N;
        scanf("%d", &L);
        while (L--) {
            scanf("%d", &N);
            if(i == 0)
                prices[i].ptr = pushback(prices[i].ptr, &prices[i].sz, newPair(N, N));
            else{
                for(int j=N; j<=BMAX; ++j){
                    if(dp[j] >= 0LL){
                        prices[i].ptr = pushback(prices[i].ptr, &prices[i].sz, newPair(N, dp[j]));
                        break;
                    }
                }
            }
        }
    }
    ll ans = -1LL;
    for(int i=0; i<K; ++i){
        for(int z=0;z<prices[i].sz;z++){pair price = prices[i].ptr[z];
            if(price.second >= B)
                ans = (ans < 0LL || ans > price.first ? price.first : ans);
        }
    }
    if(ans == -1LL)
        puts("impossible");
    else
        printf("%lld\n", ans);
    return 0;
}
