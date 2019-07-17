#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ MAX = 250000};

inline int mod10( int x ) { 
   if( x < 10 )
      return x;
   return x-10;
}
typedef struct Interval{
   int lo, hi;
   int freq[10];   
   int lazy;
   struct Interval *left, *right;
}Interval;
Interval memory[2*MAX], *allocator = memory;

Interval newInterval(){
   Interval rez={};
   return rez;
}
void rotate(Interval*x, int rot){
   static int tmp[10];
   for(int i=0; i<10; ++i)
      tmp[i] = x->freq[i];
   for(int i=0; i<10; ++i)
      x->freq[mod10(i+rot)] = tmp[i];
   x->lazy = mod10( x->lazy + rot);
}
void split(Interval*x){
   rotate(x->left , x->lazy);
   rotate(x->right, x->lazy);
   x->lazy = 0;
}
void join(Interval*x){
   for(int i=0; i<10; ++i)
      x->freq[i] = x->left->freq[i] + x->right->freq[i];
}

int n;
char start[MAX+1];

void tree_build( Interval *x ){
   if( x->lo == x->hi ) {
      x->freq[ start[x->lo]-'0' ] = 1;
   }
   else {
      int mid = (x->lo + x->hi)/2;
      x->left = allocator++;
      x->left->lo = x->lo; 
      x->left->hi = mid;
      tree_build( x->left );
      x->right = allocator++;
      x->right->lo = mid+1; 
      x->right->hi = x->hi;
      tree_build( x->right );
      join(x);
   }
}
int A, B;
int ret;

void tree_query( Interval *x ){
   if( x->lo > B || x->hi < A )
      return;
   if( A <= x->lo && x->hi <= B ){
      for( int i = 0; i < 10; ++i )
         ret += i * x->freq[i];
      rotate(x, 1);
   }
   else {
      split(x);
      tree_query( x->left );
      tree_query( x->right );
      join(x);
   }
}
int main(){
   int n, m;
   scanf( "%d%d ", &n, &m );
   gets( start );
   Interval *root = allocator++;
   root->lo = 0;
   root->hi = n-1;
   tree_build( root );
   for( int i = 0; i < m; ++i ) {
      scanf( "%d%d", &A, &B );
      --A; --B;
      ret = 0;
      tree_query( root );      
      printf( "%d\n", ret );
   }
   return 0;
}
