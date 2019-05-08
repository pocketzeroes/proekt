#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef long long ll;
enum{ MAX = 1000005};

ll a, b, period = 1ll;
int cikl[ MAX ], overflow = 0;
int n, c, d, niz[ MAX ];

int shirise( int poc, int tren, int lev ){
	if( poc == tren  &&  lev > 0 )
        return( lev );
	return( cikl[ tren ] = shirise( poc, niz[ tren ], lev + 1 ) );
}
ll gcd( ll a, ll b ) {
	while( b > 0ll ) {
		ll o = a % b;
		a = b; b = o;
	}
	return( a );
}
ll solve( ll x ){
	return( ( x + period - 1 ) / period );
}
int main(){
	scanf( "%d %lld %lld %d %d", &n, &a, &b, &c, &d );
	for( int i = 1; i <= n; ++i )
		scanf( "%d", &niz[ i ] );
	memset( cikl, -1, sizeof( cikl ) );
	for( int i = 1; i <= n; ++i )
		if( cikl[ i ] == -1 )
			shirise( i, i, 0 );
	for( int i = c+1; i <= n-d; ++i ) {
		period = ( period * cikl[ i ] ) / gcd( period, cikl[ i ] );
		if( period > b ) { overflow = 1; break; }
	}
	printf( "%lld\n", ( overflow ? 0 : solve( b ) - solve( a-1 ) ) );
	return( 0 );
}
