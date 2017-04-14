#include <stdio.h>
#include <stdint.h>

const int64_t mod = 1e9 + 7ll;
enum{ N = 5010};

int64_t dp[ N ][ N ];
int64_t split[ N ][ N ];
int n, k;

int main() {
    scanf("%d %d", &n, &k);
    dp[ 1 ][ 0 ] = 1ll;
    for ( int i = 1 ; i <= n ; ++i ) {
        for ( int j = 0 ; j < i ; ++j ) {
            dp[ i+1 ][ j+1 ] = ( dp[ i+1 ][ j+1 ] + dp[ i ][ j ] ) % mod;
            dp[ i+1 ][ j ] = ( dp[ i+1 ][ j ] + ( i - j ) * dp[ i ][ j ] ) % mod;
            if ( j > 0 ) dp[ i+1 ][ j-1 ] = ( dp[ i+1 ][ j-1 ] + j * dp[ i ][ j ] ) % mod;
        }
    }
    split[ 0 ][ 0 ] = 1ll;
    for ( int j = 1 ; j <= n ; ++j ) {
        int64_t sum = split[ 0 ][ j-1 ];
        for ( int i = 1 ; i <= n ; ++i ) {
            split[ i ][ j ] = sum;
            sum = ( sum + split[ i ][ j-1 ] ) % mod;
            if ( i - k >= 0 ) {
                sum = ( sum - split[ i-k ][ j-1 ] ) % mod;
            }
        }
    }
    int64_t ans = 0ll;
    for ( int j = 1 ; j <= n ; ++j ) {
        ans = ( ans + split[ n ][ j ] * dp[ j ][ 0 ] ) % mod;
    }
    ans = ( ans % mod + mod ) % mod;
    printf("%lld\n", ans);
    return 0;
}
