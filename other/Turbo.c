#include<stdio.h>
#include<string.h>

enum{ MAX = 100000};

int n;
int numbers [MAX+1];
int position[MAX+1];


int a[MAX+1];
void fenwick(){
  memset( a, 0, sizeof a );
}
int query( int X ) {
  int ret = 0;
  for( int x = X; x > 0; x -= x&-x )
    ret += a[x];
  return ret;
}
int sum( int lo, int hi ) {
  return query( hi ) - query( lo-1 );
}
void add( int X, int val ) {
  for( int x = X; x <= n; x += x&-x )
    a[x] += val;
}

int main(){
  scanf( "%d", &n );
  for( int i = 1; i <= n; ++i ) {
    scanf( "%d", &numbers[i] );
    position[numbers[i]] = i;
    add( i, 1 );
  }
  int mini = 1, 
      maxi = n;
  for( int i = 1; i <= n; ++i ){
    if( i%2 == 1 ){
      add( position[mini], -1 );
      printf( "%d\n", sum( 1, position[mini] ) );
      ++mini;
    }
    else{
      add( position[maxi], -1 );
      printf( "%d\n", sum( position[maxi], n ) );
      --maxi;
    }
  }
  return 0;
}
