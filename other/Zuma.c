#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

enum{ MAXN = 128       };
enum{ MAXK = 5         };
enum{ inf  = 1000000000};
int n, k;
int A[ MAXN ];
int dp[ MAXN ][ MAXN ][ MAXK ];

int solve(int l, int r, int prije){
  if( l > r )
    return 0;
  if( l == r )
    return k-1-prije;
#define ref dp[l][r][prije]
  if( ref != -1 )
    return ref;
  ref = inf;
  if( prije < k-1 )
    ref = solve( l, r, prije+1 ) + 1;
  if( prije == k-1 )
    ref = solve( l+1, r, 0 );
  for( int i = l+1; i <= r; ++i ){
      if( A[i] != A[l] )
        continue;
      int val = solve( l+1, i-1, 0 ) + solve( i, r, min( k-1, prije+1 ) );
      if( val < ref )
        ref = val;
  }
  return ref;
  #undef ref
}
int main(){
  scanf( "%d %d", &n, &k );
  for( int i = 0; i < n; ++i )
    scanf( "%d", A + i );
  memset( dp, -1, sizeof dp );
  printf( "%d\n", solve( 0, n-1, 0 ) );
  return 0;
}
