#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

#define INF 1000000000000000000LL
typedef long long ll;
ll min(ll a, ll b){return a<b?a:b;}
ll max(ll a, ll b){return a>b?a:b;}

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
ll*pushback(ll*array, int*size, ll value){
    ll*output = resizeArray(array, ll, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	ll*ptr;
	int sz;
}vec;
vec newVec(){
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
void fill(ll*arr, int sz, ll val){
    for(int i=0; i<sz; i++)
        arr[i] = val;
}
//////////////

int main() {
    ll N, K, S;
    scanf("%lld %lld %lld", &N, &K, &S);
    ll A[N];
    for (ll i = 0; i < N; ++i){
        scanf("%lld", &A[i]);
    }
    ll ic[K][S+1]; memset(ic, 0, sizeof(ic));//, 0
    for(ll i = 0; i < K; ++i){
        for (ll j = 0; j <= S; ++j){
            for (ll k = i; k < N; k += K){
                if (A[k] != j) 
                    ++ic[i][j];
            }
        }
    }
    vec interesting[K]; memset(interesting, 0, sizeof(interesting));
    for (ll i = 0; i < K; ++i){
        for (ll k = i; k < N; k += K){
            interesting[i].ptr = pushback(interesting[i].ptr, &interesting[i].sz, A[k]);
        }
    }
    ll DP[K][S+1]; for(int i=0;i<K;i++) fill(DP[i], S+1, INF);
    for (ll j = 0; j <= S; ++j){
        DP[K-1][j] = ic[K-1][j];
    }
    ll best[K][S+1]; for(int i=0; i<K; i++) fill(best[i], S+1, INF);
    best[K-1][0] = DP[K-1][0];
    for (ll j = 1; j <= S; ++j){
        best[K-1][j] = min(best[K-1][j-1], DP[K-1][j]);
    }
    for (ll i = K-2; i >= 0; --i){
        for (ll j = 0; j <= S; ++j){
            DP[i][j] = min(DP[i][j], best[i+1][j] + (N-i+K-1)/K);
            for (ll k = 0; k < interesting[i].sz; ++k){
                ll v = interesting[i].ptr[k];
                if (j-v >= 0){
                    DP[i][j] = min(DP[i][j], DP[i+1][j-v] + ic[i][v]);
                }
            }   
        }
        best[i][0] = DP[i][0];
        for (ll j = 1; j <= S; ++j){
            best[i][j] = min(best[i][j-1], DP[i][j]);
        }
    }
    printf("%lld\n", DP[0][S]);
}
