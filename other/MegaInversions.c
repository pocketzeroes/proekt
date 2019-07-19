#include<assert.h>
#include<ctype.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

enum{ N = 10000000};
#define L(i) ((i) & (~(i)+1))
typedef long long ll;

ll r[N+1],q[N+1],K,ts,cs,n,a[N];

void update_tree( ll *t, unsigned int i, ll dt ){
	for (;i <= n; t[i] += dt, i += L(i) );
}
ll prefix_sum( ll *t, unsigned int i ){
	ll w = 0;
	for (;i; w += t[i], i -= L(i) );
	return w;
}
int main() {
	int j,k;
	ll w;
	scanf("%lld",&n);
	memset(r,0,sizeof(r));
	memset(q,0,sizeof(q));
	for ( K = 0; (1UL << K) < n; ++K );
	for ( j = 0; j < n; ++j ) {
		scanf("%lld",a+j);
		update_tree( q, j+1, prefix_sum(r,n) - prefix_sum(r,a[j]) );
		update_tree( r, a[j], 1 );
	}
	memset( r, 0, sizeof(r) );
	for ( w = 0, k = 0; k < n; ++k ) {
		w += prefix_sum(r,n) - prefix_sum(r,a[k]);
		update_tree( r, a[k], prefix_sum(q,k+1)-prefix_sum(q,k) );
	}
	printf("%lld\n",w);
	return 0;
}
