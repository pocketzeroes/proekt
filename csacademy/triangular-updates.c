#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;

int main(){
  int N, Q;
  scanf("%d %d", &N, &Q );
  static ll matrix[ 4096 ][ 4096 ];
  for ( int REP_COUNTER_64 = ( int )( 0 ); REP_COUNTER_64 < ( int )( Q ); ++REP_COUNTER_64 ){
    int R, C, L, S;
    scanf("%d %d %d %d", &R, &C, &L, &S );
    --R, --C;
    const int y = R + L - 1;
    const int x = C;
    matrix[ y - L + 1 ][x] += S;
    matrix[ y - L + 1 ][ x + 1 ] -= S;
    matrix[ y + 1 ][x] -= S;
    matrix[ y + 2 ][ x + 1 ] += S;
    matrix[ y + 1 ][ x + L + 1 ] += S;
    matrix[ y + 2 ][ x + L + 1 ] -= S;
  }
  for ( int i = ( int )( 0 ); i < ( int )( N ); ++i )
    for ( int j = ( int )( 0 ); j < ( int )( N ); ++j )
      matrix[ i + 1 ][j] += matrix[i][j];
  for ( int i = ( int )( 0 ); i < ( int )( N ); ++i )
    for ( int j = ( int )( 0 ); j < ( int )( N ); ++j )
      matrix[i][ j + 1 ] += matrix[i][j];
  for ( int i = ( int )( 0 ); i < ( int )( N ); ++i )
    for ( int j = ( int )( 0 ); j < ( int )( N ); ++j )
      matrix[ i + 1 ][ j + 1 ] += matrix[i][j];
  for ( int i = ( int )( 0 ); i < ( int )( N ); ++i ){
    for ( int j = ( int )( 0 ); j < ( int )( N ); ++j )
      printf("%lld ", matrix[i][j]);
    puts("");
  }
  return 0;
}
