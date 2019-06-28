#include<stdio.h>

enum{ maxt =(int)1<<15};
int t, sol[maxt], depth[maxt];

void next( int d ){
  for( int i = t; i > 0; i-- ) {
    sol[t+i] = sol[i] = sol[i-1]*2;
    depth[t+i] = depth[i] = depth[i-1]+1;
  }
  for( int i = 1; i <= t+t; i++ )
    if( (depth[i]==d)^(i<=t) )
      sol[i]++;
  sol[0] = 1;
  depth[0] = 0;
  t = t+t+1;
}
int main(){
  depth[0] = 0;
  sol[0] = t = 1;
  int n;
  scanf( "%d", &n );
  for( int i = 1; i < n; i++ ) 
    next( i );
  for( int i = 0; i < t; i++ ) 
    printf( "%d ", sol[i] );
  return 0;
}
