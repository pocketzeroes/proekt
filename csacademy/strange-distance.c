#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
typedef struct pair {
	int first;
	int second;
}pair;
pair newPair(int a, int b) {
	pair rez;
	rez.first = a;
	rez.second = b;
	return rez;
}
int cmp (const void * pa, const void * pb)
{
    pair*a=(pair*)pa;
    pair*b=(pair*)pb;
    int diff = a->first - b->first;
    if(diff!=0)return diff;
    return a->second - b->second;
}
enum{ N = 200010};
pair points[ N ];
void update( int idx, int val );
int query( int idx );
int tree[ N ];
int64_t k;
int n;
int64_t check( int dis );


int lambda( int lo, int hi ){
    while ( lo < hi ) {
        int mid = ( lo + hi ) / 2 + 1;
        if ( check( mid ) < k ) 
            lo = mid;
        else 
            hi = mid - 1;
    }
    return lo + 1;
}
int main( void ) {
    scanf("%d %lld", &n, &k);
    for ( int i = 0 ; i < n ; ++i ) {
        scanf("%d %d", &points[i].first, &points[i].second);
    }
    qsort( points, n,sizeof(pair),cmp );
    int ans = lambda( 0, N );
    printf("%d\n", ans);
    return 0;
}
void update( int idx, int val ) {
    while ( idx < N ) {
        tree[ idx ] += val;
        idx += idx & ( -idx );
    }
}
int query( int idx ) {
    int ans = 0;
    while ( idx > 0 ) {
        ans += tree[ idx ];
        idx -= idx & ( -idx );
    }
    return ans;
}
int64_t check ( int dis ) {
    int64_t ans = 0ll;
    memset(tree, 0, sizeof(tree));
    for ( int i = 0, j = 0 ; i < n ; ++i ) {
        while ( points[j].first < points[i].first - dis ) {
            update( points[ j++ ].second, 1 );
        }
        ans += i - j
            + query( points[i].second + dis ) 
            - query( points[i].second - dis - 1 );
    }
    return ans;
}


























































