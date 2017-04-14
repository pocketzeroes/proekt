#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>

typedef struct pair{
    int first;
    int second;
}pair;
pair newPair(int a, int b){
    pair rez;
    rez.first =a;
    rez.second=b;
    return rez;
}

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
pair*pushbackP(pair*array, int *size, pair value){
    pair*output = resizeArray(array, pair, *size + 1);
    output[(*size)++] = value;
    return output;
}




typedef long long ll;
int n;
int a[100010];
pair*ans;int ansSz=0;
int*v=NULL;int vSz=0;


ll in(){ 
  long long int x; 
  scanf( "%lld" , &x ); 
  return x;
}
void swap(int*nums, int i, int j) {
   int t   = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}
void append( int l , int r , int b , bool inv){
  int st = -1;
  int en = r;
  for( ll i = (l); i < (ll)(r); i++ ){
    if( a[i] & (1LL<<(b)) ){
      if( st != -1 ){
        en = i;
        break;
      }
    }
    else if(st==-1)
      st = i;
  }
  if( st == -1 )
    return;
  assert( a[l] & (1LL<<(b)) );
  if( inv ){
    for( ll i = (st); i < (ll)(en); i++ )
      v=pushback(v,&vSz, a[i] );
    append( en , r , b , false );
  }
  else {
    append( en , r , b , true );
    for( int i = en-1; i >= st; i-- )
      v=pushback(v,&vSz, a[i] );
  }
}
void recrec( int l , int r , int b ){
  bool f = false;
  bool g = false;
  for( ll i = (l); i < (ll)(r); i++ ){
    if( a[i] & (1LL<<(b)) )
      f = true;
    else 
      g = true;
  }
  if( ( !f ) || ( !g ) )
    return;
  int m = ( l + r ) / 2;
  recrec( l , m , b );
  recrec( m , r , b );
  int x = l;
  for( int i = m-1; i >= l; i-- ){
    if( ( a[i] & (1LL<<(b)) ) == 0 ){
      x = i+1;
      break;
    }
  }
  if( x == m )
    return;
  int y = r;
  for( ll i = (m); i < (ll)(r); i++ ){
    if( a[i] & (1LL<<(b)) ){
      y = i;
      break;
    }
  }
  if( y == m )
    return;
  ans=pushbackP(ans, &ansSz, newPair( x , y ));
  int sz = y - x;
  for( ll i = (0); i < (ll)(sz / 2); i++ )
    swap(a, x+i, y-1-i );
}
void rec( int l , int r ){
  if( l == r )
    return;
  int b = 16;
  int cnt = 0;
  while( 1 ){
    for( ll i = (l); i < (ll)(r); i++ ){
      if( a[i] & (1LL<<(b)) )
        cnt++;
    }
    if( cnt )
      break;
    if( b == 0 )
      return;
    b--;
  }
  recrec( l , r , b );
  int m = r;
  for( ll i = (l); i < (ll)(r); i++ ){
    if( a[i] & (1LL<<(b)) ){
      m = i;
      break;
    }
  }
  for( ll i = (m); i < (ll)(r); i++ ){
    assert( a[i] & (1LL<<(b)) );
    a[i] -= (1LL<<(b));
  }
  rec( l , m );
  rec( m , r );
}
int main(){
  n = in();
  for( ll i = 0; i < (ll)n; i++)
    a[i] = in();
  rec( 0 , n );
  for(int i=0;i<ansSz;i++){
    pair w=ans[i];
    printf( "%d %d\n" , w.first+1 , w.second);
  }
  return 0;
}





















































