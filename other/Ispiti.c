#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int n, m;
typedef struct{
   int a, b;
   int sorted_index;
   int index;
}ucenik;
ucenik U[200000];

int pair_cmp(const void*pa, const void*pb){
   ucenik*X=(ucenik*)pa;
   ucenik*Y=(ucenik*)pb;
   if(X->b != Y->b )
      return(X->b < Y->b)?-1:1;
   return(X->a < Y->a)?-1:1;
}
int index_cmp(const void*pa, const void*pb){
   ucenik*X=(ucenik*)pa;
   ucenik*Y=(ucenik*)pb;
   return(X->index < Y->index)?-1:1;
}
typedef struct{
   int who, type;
}event;
event E[200000];
int tree[1<<19];

inline int bolji( int uc1, int uc2 ){
   if( uc1 == -1 )
      return uc2;
   if( uc2 == -1 )
      return uc1;
   if( U[uc1].a < U[uc2].a )
      return uc2;
   return uc1;
}
void update( int i, int lo, int hi, int uc ){
   if( lo > U[uc].sorted_index || hi < U[uc].sorted_index )
      return;
   if( lo == hi ){
      tree[i] = uc;
   }
   else {
      int mid = (lo+hi)/2;
      update( 2*i, lo, mid, uc );
      update( 2*i+1, mid+1, hi, uc );
      tree[i] = bolji( tree[2*i], tree[2*i+1] );
   }
}
int query( int i, int lo, int hi, int uc ){
   if( hi <= U[uc].sorted_index )
      return -1;
   if( tree[i] == -1 || U[tree[i]].a < U[uc].a )
      return -1;
   if( lo == hi )
      return tree[i];
   int mid = (lo+hi)/2;
   int t = query( 2*i, lo, mid, uc );
   if( t != -1 )
      return t;
   return query( 2*i+1, mid+1, hi, uc );
}
int main(){
   scanf( "%d", &n );
   for( int i = 0; i < n; ++i ){
      char c;
      scanf( " %c", &c );
      if( c == 'D' ){
         scanf( "%d%d", &U[m].a, &U[m].b );
         U[m].index = m;
         E[i].who   = m++;
         E[i].type  = 1;
      }
      else{
         scanf( "%d", &E[i].who ); --E[i].who;
         E[i].type = 2;
      }
   }
   qsort( U, m, sizeof(ucenik), pair_cmp);
   for( int i = 0; i < m; ++i )
      U[i].sorted_index = i;
   qsort(U, m, sizeof(ucenik), index_cmp);
   memset( tree, -1, sizeof tree );
   for( int i = 0; i < n; ++i ){
      if( E[i].type == 1 ){
         update( 1, 0, m-1, E[i].who );
      }
      else{
         int x = query( 1, 0, m-1, E[i].who );
         if( x == -1 )
            printf( "NE\n" );
         else
            printf( "%d\n", x+1 );
      }
   }
   return 0;
}
