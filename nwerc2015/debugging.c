#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
ll min(ll a, ll b){return a<b?a:b;}

ll N, T, C, table[1000005];

ll rec(int N){
	if(N <= 1)
    return 0;
	if(table[N] != LLONG_MAX)
    return table[N];
	for(int i = 1; i < N; i++){
		ll maxSegLen = (N+i)/(i+1);
		table[N] = min(table[N], i*C + T + rec(maxSegLen));
	}
	return table[N];
}
int main(){
	scanf("%lld %lld %lld", &N, &T, &C);
	for(int i = 0; i <= N; i++)
    table[i] = LLONG_MAX;
	printf("%lld\n", rec(N));
	return 0;
}
